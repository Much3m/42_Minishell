/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 03:06:43 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/30 00:49:13 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_change_pipe(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}

void	do_change_redir(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op && s[idx->i + 1] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}

t_node	*split_str(char *str)
{
	t_node		*head;
	int			i;
	int			tmp;

	i = 0;
	head = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == -1)
			i++;
		else
		{
			tmp = i;
			while (str[i] != -1 && str[i] != '\0')
				i++;
			if (head == NULL)
				head = make_new(&str[tmp], i - tmp);
			else
				add_next(make_new(&str[tmp], i - tmp), head);
		}
	}
	if (head != NULL)
		add_next(create_node(E_NULL, NULL), head);
	return (head);
}

t_node	*make_new(char *str, int size)
{
	t_node	*ptr;
	char	*ret;
	int		type;

	if (size == 0)
		return (NULL);
	ret = safe_ft_substr(str, 0, size, "make new");
	if (ret[0] == '|')
		type = E_PIPE;
	else if (ret[0] == '<' || ret[0] == '>')
		type = E_REDIR;
	else
		type = E_WORD;
	ptr = create_node(type, ret);
	return (ptr);
}

void	add_next(t_node *new, t_node *head)
{
	t_node	*ptr;

	ptr = head;
	while (ptr->left != NULL)
		ptr = ptr->left;
	ptr->left = new;
}
