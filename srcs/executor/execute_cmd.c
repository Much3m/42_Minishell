/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:29:06 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/31 12:39:32 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_node *cmd, int *fd, char **path)
{
	int		ret;
	// int		code;

	ret = -1;
	echoctl_on();
	origin_signal();
	if (do_redirect(cmd->left, fd) == -1)
		return (1);
	if (cmd->right == NULL)
		return (0);
	ret = run_builtin(cmd->right, fd);
	if (ret != -1)
		return (ret);
	execute_simcmd(cmd->right, path);
	// code = find_errno();
	if (errno == 14)
		return (print_error(fd[STD_ERROR], cmd->right->str, \
												" command not found", 127));
	else if (errno == 20 || errno == 13)
		return (print_errno(fd[STD_ERROR], cmd->right->str, NULL, 126));
	else if (errno == 2)
		return (print_errno(fd[STD_ERROR], cmd->right->str, NULL, 127));
	print_errno(fd[STD_ERROR], cmd->right->str, NULL, 1);
	return (1);
}

void	execute_simcmd(t_node *node, char **path)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strrchr(node->str, '/') != NULL || path == NULL)
	{
		tmp = safe_ft_strdup(node->str2[0], "sim_cmd");
		if (tmp == NULL)
			return ;
	}
	else
		tmp = find_path(node->str, path);
	execve(tmp, node->str2, g_envp);
}

char	*find_path(char *cmd, char **path)
{
	char		*ret;
	char		*tmp;
	int			i;
	struct stat	check;

	i = 0;
	if (cmd == NULL || cmd[0] == '\0' || path == NULL)
		return (NULL);
	while (path[i])
	{
		tmp = safe_ft_strjoin(path[i], "/", "find_path");
		ret = safe_ft_strjoin(tmp, cmd, "find_path");
		free(tmp);
		if (stat(ret, &check) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}
