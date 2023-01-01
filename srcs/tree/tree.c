/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 03:22:38 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/28 23:41:26 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(enum e_type type, char *str)
{
	t_node		*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	if (ptr == NULL)
		exit(print_errno(2, "failed to cread tree node", NULL, 1));
	ptr->type = type;
	ptr->str = str;
	ptr->str2 = NULL;
	ptr->left = NULL;
	ptr->right = NULL;
	ptr->parent = NULL;
	return (ptr);
}

t_tree	*create_tree(void)
{
	t_tree		*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		exit(print_errno(2, "fail create tree", NULL, 1));
	tree->top = NULL;
	tree->count = 0;
	return (tree);
}

void	delete_str(t_node *node)
{
	int			i;
	struct stat	check;

	i = 0;
	if (node == NULL)
		return ;
	if (node->type == E_REDIR && node->str \
		&& ft_strncmp(node->str, "<<", 3) == 0)
	{
		if (node->str2 && node->str2[0] && stat(node->str2[0], &check) == 0)
			unlink(node->str2[0]);
	}
	if (node->str != NULL)
		free(node->str);
	if (node->str2 != NULL)
	{
		while (node->str2 && node->str2[i])
			free(node->str2[i++]);
		free(node->str2);
	}
}

void	delete_nodes(t_node *node)
{
	if (node == NULL)
		return ;
	delete_nodes(node->left);
	delete_nodes(node->right);
	delete_str(node);
	free (node);
}

void	delete_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree-> top)
		delete_nodes(tree->top);
	free(tree);
}
