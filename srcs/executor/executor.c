/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 04:58:29 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 00:52:15 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_tree *tree)
{
	int		exit_status;
	pid_t	*pids;
	char	**path;

	if (tree == NULL)
		return (258);
	path = get_path(g_envp);
	exit_status = -1;
	if (tree->top->right == NULL)
		exit_status = nopipe_builtin(tree);
	if (exit_status == -1)
	{
		pids = init_pids(tree);
		if (pids == NULL)
		{
			free_path(path);
			return (1);
		}
		fork_shell(tree->top, path, pids);
		exit_status = wait_child(pids);
		main_signal();
		free(pids);
	}
	free_path(path);
	return (exit_status);
}

char	**get_path(char **list)
{
	int			i;
	char		**ret;
	char		*tmp;

	i = 0;
	ret = NULL;
	while (list[i])
	{
		if (ft_strncmp(list[i], "PATH=", 5) == 0)
		{
			tmp = safe_ft_substr(list[i], 5, \
								ft_strlen(list[i]) - 5, "get_path");
			if (tmp)
			{
				ret = ft_split(tmp, ':');
				free(tmp);
				if (ret == NULL)
					exit (print_errno(STD_ERROR, "get_path", NULL, 1));
			}
			return (ret);
		}
		i++;
	}
	return (NULL);
}

pid_t	*init_pids(t_tree *tree)
{
	t_node	*ptr;
	pid_t	*pids;
	int		count;

	ptr = tree->top;
	count = 0;
	while (ptr)
	{
		ptr = ptr->right;
		count++;
	}
	pids = safe_ft_calloc(count + 1, sizeof(pid_t), "init_pid");
	return (pids);
}

void	free_path(char **path)
{
	int			i;

	i = 0;
	if (path == NULL)
		return ;
	while (path[i])
		free(path[i++]);
	free(path);
}
