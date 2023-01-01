/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:48 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/15 13:22:49 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*temp;

	i = 0;
	temp = (const char *)s;
	while (i < n)
	{
		if (temp[i] == (char)c)
			return ((void *)(&temp[i]));
		i++;
	}
	return (NULL);
}
