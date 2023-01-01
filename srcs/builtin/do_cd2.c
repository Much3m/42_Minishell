/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:27:00 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/29 13:52:42 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_both(char *cur_dir, char *next_dir)
{
	if (cur_dir != NULL)
		free(cur_dir);
	if (next_dir != NULL)
		free(next_dir);
}

int	print_cd_erro_msg(int *fd, char *str)
{
	if (ft_strncmp(str, "-\0", 2) == 0)
	{
		ft_putendl_fd("minishell : cd: OLDPWD not set", fd[STD_ERROR]);
		return (0);
	}
	else if (ft_strncmp(str, "--", 2) == 0)
	{
		ft_putendl_fd("minishell : cd: --: invalid option", fd[STD_ERROR]);
		return (0);
	}
	else if (ft_strncmp(str, "-", 1) == 0)
	{
		ft_putstr_fd("minishell : cd: ", fd[STD_ERROR]);
		ft_putstr_fd(str, fd[STD_ERROR]);
		ft_putendl_fd(": invalid option", fd[STD_ERROR]);
		return (0);
	}
	ft_putstr_fd("minishell: cd : ", fd[STD_ERROR]);
	ft_putstr_fd(str, fd[STD_ERROR]);
	if (access(str, F_OK) != -1)
		ft_putendl_fd(": Not a directory", fd[STD_ERROR]);
	else
		ft_putendl_fd(": No such file or directory", fd[STD_ERROR]);
	return (0);
}

char	*remove_oldpwd(char *str, int *flag)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	temp = str;
	while (i < 7)
	{
		temp++;
		i++;
	}
	ret = safe_ft_strdup(temp, "copy_OLDPWD");
	(*flag) = 1;
	ft_putendl_fd(ret, 1);
	return (ret);
}

void	set_pwd_env(char *cur_dir, char *next_dir)
{
	if (cur_dir != NULL)
		g_envp = export_env(safe_ft_strjoin("OLDPWD=", cur_dir, "set_OLDPWD"));
	if (next_dir != NULL)
		g_envp = export_env(safe_ft_strjoin("PWD=", next_dir, "set_PWD"));
}
