/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:41:14 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/30 12:11:53 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_env(char *s, char **ret, int i)
{
	if (dup_export(s, g_envp[i]) == 2)
		free(s);
	else
	{
		free(g_envp[i]);
		g_envp[i] = s;
	}
	free_env(ret);
	return (g_envp);
}

int	dup_export(char *s, char *env)
{
	int	i;

	i = 0;
	if (s[i] == env[i])
	{
		while (s[i] != '=' && s[i] != '\0')
		{
			i++;
			if (s[i] != env[i])
				break ;
		}
		if (s[i] == '\0' && env[i] == '=')
			return (2);
		if ((s[i] == '=' && env[i] == '=') || \
			(s[i] == '\0' && env[i] == '\0') || (s[i] == '=' && env[i] == '\0'))
			return (1);
	}
	return (0);
}
