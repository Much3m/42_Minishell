/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:09:05 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/28 13:20:49 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_to_home(char **next_dir, int *fd)
{
	int	ch;

	ch = 0;
	ch = chdir(getenv("HOME"));
	if (ch == -1)
		return (1);
	(*next_dir) = getcwd(NULL, 0);
	if (*next_dir == NULL)
		exit (print_errno(fd[STD_ERROR], "cd", NULL, 1));
	return (0);
}

static int	cd_relative_route(char *str, char **next_dir, int *fd)
{
	int		ch;

	ch = 0;
	if (ft_strlen(str) == 1)
		return (0);
	ch = chdir("..");
	if (ch == -1)
		return (1);
	(*next_dir) = getcwd(NULL, 0);
	if (*next_dir == NULL)
		exit (print_errno(fd[STD_ERROR], "cd", NULL, 1));
	return (0);
}

static int	cd_absolute_path(char *str, char **next_dir, int *fd)
{
	int	ch;

	ch = 0;
	ch = chdir(str);
	if (ch == -1)
		return (1);
	(*next_dir) = getcwd(NULL, 0);
	if (*next_dir == NULL)
		exit (print_errno(fd[STD_ERROR], "cd", NULL, 1));
	return (0);
}

static int	cd_old_path(char **next_dir, int *fd)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (g_envp[++i])
	{
		if (ft_strncmp("OLDPWD=", g_envp[i], 7) == 0)
		{
			(*next_dir) = remove_oldpwd(g_envp[i], &flag);
			break ;
		}
	}
	if (flag == 0)
		return (1);
	if (chdir(*next_dir) == -1)
		return (1);
	if ((*next_dir) != NULL)
		free (*next_dir);
	(*next_dir) = getcwd(NULL, 0);
	if (*next_dir == NULL)
		exit (print_errno(fd[STD_ERROR], "cd", NULL, 1));
	return (0);
}

int	do_cd(char **str, int *fd)
{
	int		i;
	char	*cur_dir;
	char	*next_dir;

	i = 0;
	cur_dir = getcwd(NULL, 0);
	next_dir = NULL;
	if (cur_dir == NULL)
		exit (print_errno(fd[STD_ERROR], "cd", NULL, 1));
	if (str[1] == NULL || ft_strncmp(str[1], "~\0", 2) == 0 || \
		ft_strncmp(str[1], "--\0", 3) == 0)
		i = cd_to_home(&next_dir, fd);
	else if (ft_strncmp(str[1], ".\0", 2) == 0 || \
			ft_strncmp(str[1], "..\0", 3) == 0)
		i = cd_relative_route(str[1], &next_dir, fd);
	else if (ft_strncmp(str[1], "-\0", 2) == 0)
		i = cd_old_path(&next_dir, fd);
	else
		i = cd_absolute_path(str[1], &next_dir, fd);
	if (i == 1)
		print_cd_erro_msg(fd, str[1]);
	else if (i == 0)
		set_pwd_env(cur_dir, next_dir);
	free_both(cur_dir, next_dir);
	return (i);
}
