/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:22:33 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/27 15:41:25 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_export(char **cmd, int *fd)
{
	int			i;
	int			ret;

	i = 1;
	ret = 0;
	if (cmd[1] == NULL || cmd[1][0] == '\0')
		print_export(fd);
	else
	{
		while (cmd[i] != NULL)
		{
			if (check_environ(cmd[i], fd, 1))
				ret += 1;
			else
				g_envp = export_env(safe_ft_strdup(cmd[i], "export"));
			i++;
		}
	}
	if (ret != 0)
		ret = 1;
	return (ret);
}

void	print_export(int *fd)
{
	char		**tmp;
	int			i;
	int			j;

	i = 0;
	tmp = sorted_env();
	while (tmp[i] != NULL)
	{
		j = 0;
		ft_putstr_fd("declare -x ", fd[STD_OUT]);
		while (tmp[i][j] != '\0')
		{
			ft_putchar_fd(tmp[i][j], fd[STD_OUT]);
			if (tmp[i][j] == '=')
				ft_putstr_fd("\"", fd[STD_OUT]);
			j++;
		}
		if (is_equal(tmp[i]))
			ft_putstr_fd("\"", fd[STD_OUT]);
		ft_putstr_fd("\n", fd[STD_OUT]);
		i++;
	}
	free_env(tmp);
}

int	envp_size(void)
{
	int			i;

	i = 0;
	while (g_envp[i] != NULL)
		i++;
	return (i);
}

char	**sorted_env(void)
{
	t_index		i;
	char		**ret;
	char		*tmp;

	ret = malloc_env(envp_size() + 1);
	i.i = 0;
	i.j = 0;
	while (g_envp[++i.i] != NULL)
		ret[i.j++] = safe_ft_strdup(g_envp[i.i], "sort");
	ret[i.i] = NULL;
	i.i = -1;
	while (ret[++i.i] != NULL)
	{
		i.j = i.i;
		while (ret[++i.j] != NULL)
		{
			if (ft_strcmp(ret[i.i], ret[i.j]) > 0)
			{
				tmp = ret[i.i];
				ret[i.i] = ret[i.j];
				ret[i.j] = tmp;
			}
		}
	}
	return (ret);
}

char	**export_env(char *s)
{
	char	**ret;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = envp_size() - 1;
	ret = malloc_env(envp_size() + 2);
	while (g_envp[i] != NULL)
	{
		if (i != 0 && dup_export(s, g_envp[i]))
			return (change_env(s, ret, i));
		if (i == size)
			ret[j++] = s;
		ret[j++] = safe_ft_strdup(g_envp[i++], "change_env");
	}
	ret[j] = NULL;
	free_env(g_envp);
	return (ret);
}
