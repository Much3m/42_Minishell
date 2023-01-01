/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:07:23 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 00:49:16 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*tokenizing(char *s)
{
	t_node		*list;
	t_tree		*token;

	list = NULL;
	s = iterate_env(s);
	if (s == NULL)
		return (NULL);
	change_whitespace(s);
	s = change_oper(s);
	list = split_str(s);
	free(s);
	if (list == NULL)
		return (NULL);
	token = create_tree();
	token->top = list;
	return (token);
}

void	change_whitespace(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i += skip_quote(&s[i]);
		}
		else if (is_whitespace(s[i]))
			s[i] = -1;
		if (s[i] != '\0')
			i++;
	}
}

char	*change_oper(char *s)
{
	s = change_pipe(s, '|');
	s = change_redir(s, '<');
	s = change_redir(s, '>');
	return (s);
}

char	*change_pipe(char *s, char op)
{
	char		*str;
	t_index		*idx;
	int			k;

	idx = make_idx();
	str = malloc(sizeof(char) * (count_new_space(s, op) + 2));
	if (!str)
		malloc_error(NULL);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_quote(&s[idx->i]);
			while (k-- && s[idx->i] != '\0')
				str[idx->j++] = s[idx->i++];
		}
		do_change_pipe(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}

char	*change_redir(char *s, char op)
{
	char		*str;
	t_index		*idx;
	int			k;

	idx = make_idx();
	str = malloc(sizeof(char) * (count_new_space(s, op) + 2));
	if (!str)
		malloc_error(NULL);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_quote(&s[idx->i]);
			while (k-- && s[idx->i] != '\0')
				str[idx->j++] = s[idx->i++];
		}
		do_change_redir(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}
