/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:57:49 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 00:47:07 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_name_size(char *s)
{
	int		i;

	i = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (i + 1);
	while (s[i] != '\0')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			break ;
		i++;
	}
	return (i);
}

char	*get_env_name(char *s)
{
	int				i;
	int				j;
	char			*ret;

	j = 0;
	i = get_env_name_size(s);
	if (i == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		malloc_error("get_env");
	while (i != 0)
	{
		ret[j] = s[j];
		j++;
		i--;
	}
	ret[j] = '\0';
	return (ret);
}

char	*revert_dollar(char *str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != '\0')
		if (str[i] == -3)
			str[i] = '$';
	return (str);
}

void	check_next_dollar(char *str, int i)
{
	if (str[i + 1] == '?')
		str[i] = -2;
	else if (!(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		str[i] = -3;
	else
		str[i] = -2;
}
