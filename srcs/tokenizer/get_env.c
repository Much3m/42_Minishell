/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:08:47 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 00:47:07 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **envp)
{
	char		**list;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	list = malloc_env(i + 2);
	i = 1;
	list[0] = safe_ft_strdup("0", "get_env");
	while (envp[j])
	{
		if (ft_strncmp("OLDPWD=", envp[j], 7) == 0)
			list[i] = safe_ft_strdup("OLDPWD", "get_env");
		else
			list[i] = safe_ft_strdup(envp[j], "get_env");
		i++;
		j++;
	}
	list[i] = NULL;
	return (list);
}

char	*iterate_env(char *s)
{
	t_index		*i;
	char		*str;

	i = make_idx();
	str = safe_ft_strdup(s, "get_env");
	while (str[i->i] != '\0')
	{
		if (str[i->i] == '\"')
			i->j = is_iterate(&str[i->i], i->j);
		if (str[i->i] == '\'' && i->j == 0)
			i->i += skip_quote(&str[i->i]);
		if (str[i->i] == '$')
		{
			check_next_dollar(str, i->i);
			if (str[i->i] == -2)
				str = get_converted_str(str, i);
			if (str == NULL)
				break ;
		}
		else if (str[i->i] != '\0')
			i->i++;
	}
	free(i);
	return (revert_dollar(str));
}

char	*convert_env_to_str(char *env)
{
	t_index	i;

	i.i = -1;
	i.j = 0;
	if (env == NULL)
		return (NULL);
	if (env[0] == '?' && env[1] == '\0')
		return (free_ret(env, g_envp[0]));
	while (g_envp[++i.i] != NULL)
	{
		if (env[0] == g_envp[i.i][0])
		{
			while (env[i.j] != '\0' && g_envp[i.i][i.j] \
			!= '\0' && g_envp[i.i][i.j] != '=')
			{
				if (env[i.j] != g_envp[i.i][i.j])
					break ;
				i.j++;
			}
			if (env[i.j] == '\0' && g_envp[i.i][i.j] == '=')
				return (free_ret(env, &g_envp[i.i][++i.j]));
		}
		i.j = 0;
	}
	return (free_ret(env, NULL));
}

char	*get_converted_str(char *s, t_index *i)
{
	char	*env;

	env = convert_env_to_str(get_env_name(&s[i->i + 1]));
	i->i += ft_strlen(env);
	s = get_merged_env_str(s, env);
	return (s);
}

char	*get_merged_env_str(char *s, char *env)
{
	int		i;
	char	*front;
	char	*rear;
	char	*merge1;
	char	*merge2;

	i = 0;
	while (s[i] != -2)
		i++;
	if (i != 0)
		front = safe_ft_substr(s, 0, i, "get_env");
	else
		front = NULL;
	if (s[get_env_name_size(&s[i + 1]) + i + 1] != '\0')
		rear = safe_ft_strdup(&s[get_env_name_size(&s[i + 1]) \
		+ i + 1], "get_env");
	else
		rear = NULL;
	merge1 = ft_strjoin_check_null(front, env);
	merge2 = ft_strjoin_check_null(merge1, rear);
	free(s);
	return (merge2);
}
