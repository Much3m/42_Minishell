/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:04:07 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/26 17:36:02 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(int *fd)
{
	int			i;

	i = 1;
	while (g_envp[i])
	{
		if (is_equal(g_envp[i]))
		{
			ft_putstr_fd(g_envp[i], fd[STD_OUT]);
			ft_putstr_fd("\n", fd[STD_OUT]);
		}
		i++;
	}
	return (0);
}

int	is_equal(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
