/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:23:06 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/16 18:52:20 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int				i;
	char			*temp;

	if (!s || fd < 0)
		return ;
	temp = s;
	i = 0;
	while (temp[i])
	{
		ft_putchar_fd(temp[i], fd);
		i++;
	}
}
