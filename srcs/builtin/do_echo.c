/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:59:42 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/27 16:10:52 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_option(char **str, int *new_line_flag)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] != '-')
			return (i);
		j++;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
		if (i == 2)
			*new_line_flag = 1;
	}
	return (i);
}

int	do_echo(char **str, int *fd)
{
	int	i;
	int	new_line_flag;

	i = 1;
	new_line_flag = 0;
	if (str[i] == NULL)
	{
		ft_putstr_fd("\n", fd[STD_ERROR]);
		return (0);
	}
	i = check_n_option(str, &new_line_flag);
	while (str[i])
	{
		ft_putstr_fd(str[i], fd[STD_OUT]);
		if (str[++i])
			ft_putstr_fd(" ", fd[STD_OUT]);
	}
	if (!new_line_flag)
		ft_putstr_fd("\n", fd[STD_OUT]);
	return (0);
}
