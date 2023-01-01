/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:11:42 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/28 20:24:47 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_exit_message(int *fd, int flag, char *str)
{
	if (flag == 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", fd[STD_ERROR]);
		return (1);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: exit: ", fd[STD_ERROR]);
		ft_putstr_fd(str, fd[STD_ERROR]);
		ft_putendl_fd(": numeric argument required", fd[STD_ERROR]);
		return (255);
	}
	return (0);
}

static int	check_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	do_exit(char **str, int *fd)
{
	long long	i;
	int			flag;

	i = 0;
	flag = 1;
	while (str[i])
		i++;
	if (i > 2)
		return (print_exit_message(fd, 1, NULL));
	else if (i == 1)
		exit (0);
	flag = check_is_digit(str[1]);
	i = ft_atoll(str[1], &flag);
	if (flag == 0 && str[1] != NULL)
		i = print_exit_message(fd, 2, str[1]);
	exit (i % 256);
}
