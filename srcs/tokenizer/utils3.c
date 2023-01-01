/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:13:05 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 22:20:23 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(char *s)
{
	print_errno(STD_ERROR, s, NULL, -1);
	exit(1);
}

char	*ft_strjoin_check_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = safe_ft_strjoin(s1, s2, "make_str");
		free(s1);
		free(s2);
		return (result);
	}
	if (s1 == NULL && s2 != NULL)
	{
		result = safe_ft_strdup(s2, "make_str");
		free(s2);
		return (result);
	}
	if (s1 != NULL && s2 == NULL)
	{
		result = safe_ft_strdup(s1, "make_str");
		free(s1);
		return (result);
	}
	return (NULL);
}

char	*del_dequote(char **str)
{
	char		*s;
	char		*ret;
	t_index		*idx;

	s = *str;
	idx = make_idx();
	ret = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ret == NULL)
		malloc_error("del_deqoute");
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"')
			do_del_dequote(ret, s, '\"', idx);
		else if (s[idx->i] == '\'')
			do_del_dequote(ret, s, '\'', idx);
		else
			ret[idx->j++] = s[idx->i++];
	}
	ret[idx->j] = '\0';
	free(s);
	free(idx);
	*str = ret;
	return (ret);
}

void	do_del_dequote(char *new, char *s, char c, t_index *idx)
{
	if (check_dequote(&s[idx->i]))
	{
		idx->i++;
		while (s[idx->i] != c)
			new[idx->j++] = s[idx->i++];
		idx->i++;
	}
	else
		new[idx->j++] = s[idx->i++];
}

int	check_dequote(char *s)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\"')
					return (1);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\'')
					return (1);
		}
		else
			i++;
	}
	return (0);
}
