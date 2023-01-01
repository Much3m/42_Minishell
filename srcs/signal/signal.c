/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:16:19 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/29 22:20:23 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	origin_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	int_hanlder(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STD_ERROR);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	modify_exit_status(1);
}

void	main_signal(void)
{
	echoctl_off();
	signal(SIGINT, int_hanlder);
	signal(SIGQUIT, SIG_IGN);
}

void	modify_exit_status(int n)
{
	free(g_envp[0]);
	g_envp[0] = ft_itoa(n);
	if (g_envp[0] == NULL)
		malloc_error("exit_status");
}
