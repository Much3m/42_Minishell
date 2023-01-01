/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:19:35 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/22 19:22:33 by seowokim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_tree **tokens)
{
	t_tree	*tree;
	t_node	*curr_pipe;
	int		ret;

	tree = create_tree();
	add_pipe_cmd(tree, NULL, NULL);
	curr_pipe = tree->top;
	while (1)
	{
		ret = check_type(tree, *tokens, &curr_pipe);
		if (ret == -2)
		{
			curr_pipe = curr_pipe->right;
			continue ;
		}
		else if (ret != 0)
		{
			delete_tree(tree);
			tree = NULL;
		}
		break ;
	}
	delete_tree(*tokens);
	(*tokens) = tree;
	return (ret);
}

int	check_type(t_tree *tree, t_tree *tokens, t_node **curr_pipe)
{
	int		ret;
	t_node	*curr_cmd;
	t_node	*next;
	t_node	*curr;

	curr_cmd = (*curr_pipe)->left;
	curr = tokens->top;
	next = tokens->top->left;
	if (curr->type == E_WORD && del_dequote(&curr->str))
		ret = parse_word(tree, tokens, curr_cmd, next);
	else if (curr->type == E_REDIR)
		ret = parse_redirect(tree, tokens, curr_cmd, next);
	else if (curr->type == E_NULL)
		ret = 0;
	else
	{
		parse_error(curr->str);
		ret = 258;
	}
	return (ret);
}

void	parse_error(char *s)
{
	if (s == NULL)
		print_error(STD_ERROR, \
		"syntax error near unexpected token 'newline'", NULL, 1);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '" \
		, STD_ERROR);
		ft_putstr_fd(s, STD_ERROR);
		ft_putstr_fd("'\n", STD_ERROR);
	}
}
