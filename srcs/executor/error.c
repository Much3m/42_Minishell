/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:14:08 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 15:07:23 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_errno(int fd, char *s1, char *s2, int ret)
{
	ft_putstr_fd("minishell: ", fd);
	if (s1 != NULL)
	{
		ft_putstr_fd(s1, fd);
		ft_putstr_fd(": ", fd);
	}
	if (s2 != NULL)
	{
		ft_putstr_fd(s2, fd);
		ft_putstr_fd(": ", fd);
	}
	perror(NULL);
	return (ret);
}

int	print_error(int fd, char *s1, char *s2, int ret)
{
	ft_putstr_fd("minishell: ", fd);
	if (s1 != NULL)
		ft_putstr_fd(s1, fd);
	if (s2 != NULL)
	{
		ft_putstr_fd(":", fd);
		ft_putstr_fd(s2, fd);
	}
	ft_putstr_fd("\n", fd);
	return (ret);
}

void	read_error_log(t_index *i, char *buff)
{
	i->i = open("error_log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(i->i, 2);
	perror(NULL);
	close(i->i);
	i->i = open("error_log", O_RDONLY);
	i->k = read(i->i, buff, 100);
	buff[i->k] = '\0';
	close(i->i);
}

int	find_errno(void)
{
	t_index		*i;
	char		*buff;
	int			backup;

	i = make_idx();
	buff = safe_ft_calloc(101, 1, "find_errno");
	backup = dup(2);
	while (i->j <= 106)
	{
		read_error_log(i, buff);
		if (ft_strncmp(strerror(i->j), buff, ft_strlen(buff) - 1) == 0)
			break ;
		ft_memset(buff, 0, 101);
		i->j++;
	}
	dup2(backup, 2);
	close(backup);
	unlink("error_log");
	free(buff);
	backup = i->j;
	free(i);
	return (backup);
}
