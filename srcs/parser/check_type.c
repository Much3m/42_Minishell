/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:17:52 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/22 16:17:41 by seowokim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alltype(t_tree *tree, t_tree *tokens, t_node *curr_cmd)
{
	int		ret;
	t_node	*next;

	ret = 258;
	next = tokens->top->left;
	if (tokens->top->type == E_WORD && del_dequote(&tokens->top->str))
		ret = parse_word(tree, tokens, curr_cmd, next);
	else if (tokens->top->type == E_REDIR)
		ret = parse_redirect(tree, tokens, curr_cmd, next);
	else if (tokens->top->type == E_PIPE)
		ret = parse_pipe(tree, tokens, &curr_cmd->parent);
	else if (tokens->top->type == E_NULL)
		ret = 0;
	else
		parse_error(tokens->top->str);
	return (ret);
}

int	parse_word(t_tree *tree, t_tree *tokens, t_node *curr_cmd, \
				t_node *curr_tokens)
{
	int		ret;

	ret = 258;
	if (tree == NULL || tokens == NULL || \
		curr_cmd == NULL || curr_tokens == NULL)
		return (ret);
	if (curr_tokens->type == E_WORD && del_dequote(&curr_tokens->str))
		ret = parse_word(tree, tokens, curr_cmd, curr_tokens->left);
	else
	{
		if (add_simcmd(tree, tokens, curr_cmd) == -1)
			return (ret);
		ret = check_alltype(tree, tokens, curr_cmd);
	}
	return (ret);
}

int	parse_redirect(t_tree *tree, t_tree *tokens, \
					t_node *curr_cmd, t_node *curr_token)
{
	int			ret;

	ret = 258;
	if (tree == NULL || tokens == NULL || \
		curr_cmd == NULL || curr_token == NULL)
		return (ret);
	if (curr_token->type == E_WORD && del_dequote(&curr_token->str))
	{
		ret = add_redirect(tree, tokens, curr_cmd);
		if (ret == 0)
			ret = check_alltype(tree, tokens, curr_cmd);
	}
	else
		parse_error(curr_token->str);
	return (ret);
}

int	parse_pipe(t_tree *tree, t_tree *tokens, t_node **curr_pipe)
{
	int			ret;

	ret = add_pipe_cmd(tree, tokens, *curr_pipe);
	if (tokens->top->type == E_WORD && del_dequote(&tokens->top->str))
		ret = -2;
	else if (tokens->top->type == E_REDIR)
		ret = -2;
	else
	{
		parse_error(tokens->top->str);
		ret = 258;
	}
	return (ret);
}
