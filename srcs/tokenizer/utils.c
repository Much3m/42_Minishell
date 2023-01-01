/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:05:15 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 22:25:16 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	check_only_space(char *s)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_whitespace(s[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	skip_quote(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\"' && s[i] != '\0')
				i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\'' && s[i] != '\0')
				i++;
	}
	if (s[i] == '\0')
		return (0);
	return (i);
}

int	count_new_space(char *s, char c)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count += 2;
		i++;
	}
	return (i + count);
}

void	quit_by_signal(int status)
{
	if ((status & 255) != 0)
	{
		if ((status & 255) == 2)
			ft_putstr_fd("\n", STD_ERROR);
		else if ((status & 255) == 3)
			ft_putstr_fd("Quit: 3\n", STD_ERROR);
	}
}
