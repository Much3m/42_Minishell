/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:35:45 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 14:21:34 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*fork_shell(t_node *pipe, char **path, pid_t *pids)
{
	int			i;
	int			pipe_fd[2];
	int			*fd;

	i = 0;
	init_fd(&fd);
	while (pipe)
	{
		set_pipe_write(pipe, pipe_fd, fd);
		fork_signal();
		pids[i] = fork();
		if (pids[i] == -1)
			print_errno(STD_ERROR, "fork failed", NULL, 1);
		if (pids[i++] == 0)
		{
			if (pipe->right)
				ft_close(pipe_fd[PIPE_READ]);
			exit(execute_cmd(pipe->left, fd, path));
		}
		set_pipe_read(pipe, pipe_fd, fd);
		pipe = pipe->right;
	}
	free(fd);
	return (pids);
}

void	set_pipe_write(t_node *node, int *pipe_fd, int *fd)
{
	if (node->right)
	{
		if (pipe(pipe_fd) == -1)
		{
			print_errno(STD_ERROR, "set_pipe", NULL, -1);
			pipe_fd[STD_IN] = -1;
			pipe_fd[STD_OUT] = -1;
		}
		fd[STD_OUT] = pipe_fd[PIPE_WRITE];
	}
	else
		fd[STD_OUT] = STD_OUT;
}

void	set_pipe_read(t_node *node, int *pipe_fd, int *fd)
{
	if (fd[STD_IN] > 2)
		ft_close(fd[STD_IN]);
	if (node->right)
	{
		fd[STD_IN] = pipe_fd[PIPE_READ];
		ft_close(fd[STD_OUT]);
	}
}

int	wait_child(int *pids)
{
	int			i;
	int			statloc;
	int			status;

	i = 0;
	status = 1;
	if (pids[i] == 0)
		return (status);
	while (pids[i])
	{
		if (pids[i] == -1)
			status = -1;
		waitpid(pids[i], &statloc, 0);
		i++;
	}
	if (status == -1)
		return (1);
	quit_by_signal(statloc);
	status = iterate_statloc(statloc);
	return (status);
}
