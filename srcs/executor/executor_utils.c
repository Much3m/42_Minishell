/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 05:12:46 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/27 14:10:24 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fd(int **fd)
{
	if (fd == NULL)
		return (-1);
	(*fd) = safe_ft_calloc(3, sizeof(int), "fail init fd");
	(*fd)[0] = STD_IN;
	(*fd)[1] = STD_OUT;
	(*fd)[2] = STD_ERROR;
	return (1);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		print_errno(STD_ERROR, NULL, NULL, 1);
}

int	iterate_statloc(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc >> 8) & 255);
	return ((statloc & 255) + 128);
}
