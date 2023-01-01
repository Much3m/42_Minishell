/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:23:10 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/15 13:23:12 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free(char **s)
{
	int				i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

size_t	count_word(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_dup(char const *s, char c)
{
	size_t	len;
	char	*ret;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}

void	write_split(char **ptr, char const *s, char c, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && s[j])
	{
		if (s[j] != c)
		{
			ptr[i++] = ft_dup(&s[j], c);
			if (!ptr)
			{
				ft_free(ptr);
				return ;
			}
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	len;

	if (!s)
		return (NULL);
	len = count_word(s, c);
	ptr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	write_split(ptr, s, c, len);
	return (ptr);
}
