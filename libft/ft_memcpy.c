/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:52 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/16 15:01:47 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (const unsigned char *)src;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}
