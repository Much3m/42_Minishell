/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 05:14:35 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/27 14:08:31 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redirect(t_node *node, int *fd)
{
	if (fd == NULL || fd[STD_IN] == -1 || fd[STD_OUT] == -1)
		return (-1);
	if (set_redirection(node, fd) == NULL)
		return (-1);
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)
		return (print_errno(STD_ERROR, "redirection", NULL, -1));
	if (fd[STD_OUT] != STD_OUT && dup2(fd[STD_OUT], STD_OUT) == -1)
		return (print_errno(STD_ERROR, "redirection", NULL, -1));
	if (fd[STD_ERROR] != STD_IN && dup2(fd[STD_ERROR], STD_ERROR) == -1)
		return (print_errno(STD_ERROR, "redirection", NULL, -1));
	return (1);
}

int	*set_redirection(t_node *node, int *fd)
{
	while (node)
	{
		if (check_redirection_type(node, fd) == -1)
			return (NULL);
		node = node->left;
	}
	return (fd);
}
