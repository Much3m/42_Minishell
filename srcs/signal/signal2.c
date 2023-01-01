/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:06:34 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/28 17:01:02 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echoctl_off(void)
{
	struct termios	set;

	tcgetattr(1, &set);
	set.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &set);
}

void	echoctl_on(void)
{
	struct termios	set;

	tcgetattr(1, &set);
	set.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &set);
}

void	eof_handler(void)
{
	ft_putstr_fd("\033[1A", STD_ERROR);
	ft_putstr_fd("\033[12C", STD_ERROR);
	ft_putstr_fd("exit\n", STD_ERROR);
}

void	heredoc_signal(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STD_ERROR);
	exit(1);
}
