/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:54 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/16 15:05:22 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char		*tmp;
	const char	*s;

	if (dest == src || count == 0)
		return (dest);
	if (dest < src)
	{
		tmp = dest;
		s = src;
		while (count--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = dest;
		tmp += count;
		s = src;
		s += count;
		while (count--)
			*(--tmp) = *(--s);
	}
	return (dest);
}
