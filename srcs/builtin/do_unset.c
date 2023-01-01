/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:00:15 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 12:09:52 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_unset(char **sim_cmd, int *fd)
{
	t_index	*idx;

	idx = make_idx();
	idx->k = 1;
	while (sim_cmd[idx->k] != NULL)
	{
		check_environ(sim_cmd[idx->k], fd, 0);
		while (g_envp[idx->i] != NULL)
		{
			if (idx->i != 0 && check_dup(sim_cmd[idx->k], g_envp[idx->i]))
				unset_envp_list(idx);
			idx->i++;
		}
		idx->i = 0;
		idx->k++;
	}
	free(idx);
	return (0);
}

void	unset_envp_list(t_index *idx)
{
	free(g_envp[idx->i]);
	while (g_envp[idx->i + 1] != NULL)
	{
		g_envp[idx->i] = g_envp[idx->i + 1];
		idx->i++;
	}
	g_envp[idx->i] = g_envp[idx->i + 1];
}

int	check_environ(char *word, int *fd, int is_export)
{
	int	i;

	i = 0;
	if ((ft_isalpha(word[0]) == 0 && word[0] != '_') && is_export)
		return (error_unset_export("export: ", ": not a valid identifier", \
									word, fd));
	else if ((ft_isalpha(word[0]) == 0 && word[0] != '_') && !is_export)
		return (error_unset_export("unset: ", ": not a valid identifier", \
				word, fd));
	while (word[i] != '\0' && word[i] != '=')
	{
		if (!(ft_isalnum(word[i]) || word[i] == '_') && is_export)
			return (error_unset_export("export: ", ": not a valid identifier", \
			word, fd));
		else if (!(ft_isalnum(word[i]) || word[i] == '_') && !is_export)
			return (error_unset_export("unset: ", ": not a valid identifier", \
			word, fd));
		i++;
	}
	return (0);
}

int	error_unset_export(char *command, char *str, char *word, int *fd)
{
	ft_putstr_fd("minishell: ", fd[STD_ERROR]);
	ft_putstr_fd(command, fd[STD_ERROR]);
	ft_putstr_fd("`", fd[STD_ERROR]);
	ft_putstr_fd(word, fd[STD_ERROR]);
	ft_putstr_fd("\'", fd[STD_ERROR]);
	ft_putstr_fd(str, fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	return (1);
}

int	check_dup(char *s, char *env)
{
	int		i;

	i = 0;
	if (s[i] == env[i])
	{
		while (s[i] != '\0')
		{
			i++;
			if (s[i] != env[i])
				break ;
		}
		if (s[i] == '\0' && (env[i] == '=' || env[i] == '\0'))
			return (1);
	}
	return (0);
}
