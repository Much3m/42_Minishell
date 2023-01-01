/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 05:16:12 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/23 14:45:20 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_type(t_node *node, int *fd)
{
	if (strncmp(node->str, "<", 2) == 0)
		redirection_in(node, fd);
	else if (strncmp(node->str, ">", 2) == 0)
		redirection_out(node, fd);
	else if (strncmp(node->str, ">>", 3) == 0)
		redirection_append(node, fd);
	else if (strncmp(node->str, "<<", 3) == 0)
		redirection_heredoc(node, fd);
	else
		return (-1);
	return (1);
}

void	redirection_in(t_node *node, int *fd)
{
	if (fd[STD_IN] > 2)
		ft_close(fd[STD_IN]);
	fd[STD_IN] = open(node->str2[0], O_RDONLY);
	if (fd[STD_IN] == -1)
		exit (print_errno(fd[STD_ERROR], node->str2[0], NULL, 1));
}

void	redirection_out(t_node *node, int *fd)
{
	if (fd[STD_OUT] > 2)
		ft_close(fd[STD_OUT]);
	fd[STD_OUT] = open(node->str2[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[STD_OUT] == -1)
		exit (print_errno(fd[STD_ERROR], node->str2[0], NULL, 1));
}

void	redirection_append(t_node *node, int *fd)
{
	if (fd[STD_OUT] > 2)
		ft_close(fd[STD_OUT]);
	fd[STD_OUT] = open(node->str2[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[STD_OUT] == -1)
		exit (print_errno(fd[STD_ERROR], node->str2[0], NULL, 1));
}

void	redirection_heredoc(t_node *node, int *fd)
{
	if (fd[STD_IN] > 2)
		ft_close(fd[STD_IN]);
	fd[STD_IN] = open(node->str2[0], O_RDONLY);
	if (fd[STD_IN] == -1)
		exit (print_errno(fd[STD_ERROR], node->str2[0], NULL, 1));
	unlink(node->str2[0]);
}
