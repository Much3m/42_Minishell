/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:21:00 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 16:45:11 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*pop_tokens(t_tree *tree)
{
	t_node	*ret;

	if (tree == NULL || tree->top == NULL)
		return (NULL);
	ret = tree->top;
	tree->top = tree->top->left;
	if (tree->top)
		tree->top->parent = NULL;
	if (ret->left)
		ret->left = NULL;
	tree->count--;
	return (ret);
}

int	add_pipe_cmd(t_tree *tree, t_tree *token, t_node *curr)
{
	t_node		*new;

	if (tree == NULL)
		return (-1);
	if (token == NULL)
		new = create_node(E_PIPE, NULL);
	else
		new = pop_tokens(token);
	if (new == NULL)
		exit(print_errno(STD_ERROR, "faild to add pipe", NULL, 1));
	new->left = create_node(E_CMD, NULL);
	new->left->parent = new;
	if (curr == NULL && tree->top == NULL)
		tree->top = new;
	else
		curr->right = new;
	return (1);
}

int	count_wordtype(t_node *node)
{
	int			cnt;

	cnt = 0;
	while (node->type == E_WORD)
	{
		node = node->left;
		cnt++;
	}
	return (cnt);
}

int	add_redirect(t_tree *tree, t_tree *tokens, t_node *curr_cmd)
{
	t_node	*redir;
	t_node	*file;
	int		ret;

	if (tree == NULL || tokens == NULL || curr_cmd == NULL)
		return (-1);
	redir = pop_tokens(tokens);
	file = pop_tokens(tokens);
	redir->str2 = safe_ft_calloc(2, sizeof(char *), "fail to add redirect");
	redir->str2[0] = file->str;
	redir->str2[1] = NULL;
	if (curr_cmd->left != NULL)
	{
		curr_cmd = curr_cmd->left;
		while (curr_cmd->left)
			curr_cmd = curr_cmd->left;
	}	
	curr_cmd->left = redir;
	redir->parent = curr_cmd;
	tree->count++;
	free(file);
	ret = 0;
	if (ft_strncmp(redir->str, "<<", 3) == 0)
		ret = do_heredoc(*redir->str2, redir);
	return (ret);
}
