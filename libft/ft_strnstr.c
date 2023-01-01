/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:23:30 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/16 15:37:01 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)(&haystack[i]));
			j++;
		}
		i++;
	}
	return (0);
}
