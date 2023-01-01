/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_simplecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:16:37 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/23 14:38:16 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd)
{
	t_node	*token;
	t_node	*tmp;
	int		count;

	if (tree == NULL || tokens == NULL || tree->top == NULL || cur_cmd == NULL)
		return (-1);
	if (cur_cmd->right == NULL)
		simcmd_new(tokens, cur_cmd);
	else
		simcmd_append(tokens, cur_cmd->right);
	token = cur_cmd->right;
	count = 1;
	while (token->str2[count])
		count++;
	while (tokens->top->type == E_WORD)
	{
		tmp = pop_tokens(tokens);
		token->str2[count++] = tmp->str;
		free(tmp);
	}
	token->str2[count] = NULL;
	return (1);
}

void	simcmd_new(t_tree *tokens, t_node *curr_cmd)
{
	t_node		*token;

	token = pop_tokens(tokens);
	token->type = E_SIMPLE_CMD;
	curr_cmd->right = token;
	token->str2 = safe_ft_calloc(count_wordtype(tokens->top) + 2, \
								sizeof(char *), "fail to add simcmd");
	token->str2[0] = safe_ft_strdup(token->str, "fail to add simcmd");
	token->str2[1] = NULL;
}

void	simcmd_append(t_tree *tokens, t_node *node)
{
	int				i;
	char			**ret;

	i = 0;
	while (node->str2[i])
		i++;
	ret = safe_ft_calloc(count_wordtype(tokens->top) + i + 1, \
						sizeof(char *), "fali to add simcmd");
	i = 0;
	while (node->str2[i])
	{
		ret[i] = node->str2[i];
		i++;
	}
	ret[i] = NULL;
	free (node->str2);
	node->str2 = ret;
}
