/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:10:08 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 22:20:25 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_env(int size)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * size);
	if (!ret)
		malloc_error("malloc_env");
	while (i != size)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}

t_index	*make_idx(void)
{
	t_index	*ret;

	ret = malloc(sizeof(t_index));
	if (!ret)
		malloc_error("makde_idx");
	ret->i = 0;
	ret->j = 0;
	ret->k = 0;
	return (ret);
}

void	free_env(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
