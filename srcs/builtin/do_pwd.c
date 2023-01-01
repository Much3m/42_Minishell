/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 06:19:22 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/27 23:06:33 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(int *fd)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
		exit (print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
