/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:27:41 by seowokim          #+#    #+#             */
/*   Updated: 2023/01/01 21:18:41 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_tmp_file(void)
{
	char		*ret;
	// int			code;
	int			i;
	char		*n;
	struct stat	check;

	i = 0;
	ret = safe_ft_strjoin("/tmp/mini_tmp_", "0", "heredoc");
	while (ret && stat(ret, &check) != -1)
	{
		i++;
		free(ret);
		n = ft_itoa(i);
		ret = safe_ft_strjoin("/tmp/mini_tmp_", n, "heredoc");
		free(n);
	}
	// code = find_errno();
	if (errno != 2)
	{
		free (ret);
		ret = NULL;
	}
	return (ret);
}

int	do_heredoc(char *str, t_node *redir)
{
	char		*tmp_file;
	int			status;
	int			ret;
	pid_t		pid;

	tmp_file = create_tmp_file();
	if (tmp_file == NULL)
		return (print_errno(STD_ERROR, "heredoc", NULL, 2));
	pid = fork();
	if (pid == 0)
		exit(fork_heredoc(str, tmp_file));
	else if (pid == -1)
	{
		free(tmp_file);
		return (print_errno(STD_ERROR, "fork_heredoc", NULL, 2));
	}
	fork_signal();
	waitpid(pid, &status, 0);
	main_signal();
	ret = iterate_statloc(status);
	free(redir->str2[0]);
	redir->str2[0] = tmp_file;
	return (ret);
}

int	fork_heredoc(char *key, char *tmp_file)
{
	int				fd;
	char			*buf;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return (print_errno(STD_ERROR, "write_heredoc", NULL, 1));
	heredoc_signal();
	buf = readline("> ");
	while (buf)
	{
		if (ft_strncmp(buf, key, ft_strlen(key) + 1) != 0)
			ft_putendl_fd(buf, fd);
		else
		{
			free(buf);
			break ;
		}
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			ft_putstr_fd("\033[1A\033[2C", STD_ERROR);
	}
	close(fd);
	return (0);
}
