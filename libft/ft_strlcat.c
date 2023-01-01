/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:23:20 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/16 15:07:58 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t				i;
	size_t				size_of_src;
	size_t				size_of_dest;

	size_of_src = ft_strlen(src);
	size_of_dest = ft_strlen(dest);
	i = 0;
	if (size <= size_of_dest)
		return (size_of_src + size);
	while (src[i] != '\0' && i < size - size_of_dest - 1)
	{
		*(dest + size_of_dest + i) = *(src + i);
		i++;
	}
	*(dest + size_of_dest + i) = '\0';
	return (size_of_src + size_of_dest);
}
