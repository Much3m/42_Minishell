/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:24:27 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 15:31:57 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_ret(char *env, char *str)
{
	free(env);
	if (str == NULL)
		return (NULL);
	return (safe_ft_strdup(str, "get_env"));
}

int	is_iterate(char *s, int double_flag)
{
	if (double_flag == 1)
		double_flag = 0;
	else if (skip_quote(s) != 0 && double_flag == 0)
		double_flag = 1;
	return (double_flag);
}
