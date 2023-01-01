/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:11:50 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 22:20:23 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_ft_strjoin(char *s1, char *s2, char *s3)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (new == NULL)
		malloc_error(s3);
	return (new);
}

char	*safe_ft_strdup(char *s1, char *s2)
{
	char	*new;

	new = ft_strdup(s1);
	if (new == NULL)
		malloc_error(s2);
	return (new);
}

char	*safe_ft_substr(char *s1, int start, int size, char *s2)
{
	char	*new;

	new = ft_substr(s1, start, size);
	if (new == NULL)
		malloc_error(s2);
	return (new);
}

void	*safe_ft_calloc(size_t count, size_t size, char *s)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (ret == NULL)
		malloc_error(s);
	return (ret);
}
