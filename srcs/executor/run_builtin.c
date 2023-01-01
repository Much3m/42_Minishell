/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 05:05:29 by min-skim          #+#    #+#             */
/*   Updated: 2022/12/23 18:33:41 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_node *sim_cmd, int *fd)
{
	int			ret;

	ret = 0;
	if (sim_cmd->str == NULL)
		return (-1);
	if (fd == NULL)
		return (-1);
	if (ft_strncmp(sim_cmd->str, "echo", 5) == 0)
		ret = do_echo(sim_cmd->str2, fd);
	else if (ft_strncmp(sim_cmd->str, "cd", 3) == 0)
		ret = do_cd(sim_cmd->str2, fd);
	else if (ft_strncmp(sim_cmd->str, "env", 4) == 0)
		ret = do_env(fd);
	else if (ft_strncmp(sim_cmd->str, "export", 7) == 0)
		ret = do_export(sim_cmd->str2, fd);
	else if (ft_strncmp(sim_cmd->str, "pwd", 3) == 0)
		ret = do_pwd(fd);
	else if (ft_strncmp(sim_cmd->str, "unset", 6) == 0)
		ret = do_unset(sim_cmd->str2, fd);
	else if (ft_strncmp(sim_cmd->str, "exit", 5) == 0)
		ret = do_exit(sim_cmd->str2, fd);
	else
		return (-1);
	return (ret);
}

int	nopipe_builtin(t_tree *tree)
{
	int		exit_status;
	int		*fd;
	t_node	*cmd;
	t_node	*sim_cmd;

	exit_status = 1;
	cmd = tree->top->left;
	sim_cmd = cmd->right;
	if (tree->top->right || sim_cmd == NULL || cmd == NULL)
		return (-1);
	if (is_builtin(sim_cmd) == -1)
		return (-1);
	if (init_fd(&fd) == -1)
		return (exit_status);
	if (set_redirection(cmd->left, fd))
		exit_status = run_builtin(sim_cmd, fd);
	if (fd[STD_IN] > 2)
		ft_close(fd[STD_IN]);
	if (fd[STD_OUT] > 2)
		ft_close(fd[STD_OUT]);
	if (fd[STD_ERROR] > 2)
		ft_close(fd[STD_ERROR]);
	free(fd);
	return (exit_status);
}

int	is_builtin(t_node *sim_cmd)
{
	if (sim_cmd == NULL || sim_cmd->str == NULL)
		return (-1);
	if (ft_strncmp(sim_cmd->str, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(sim_cmd->str, "exit", 5) == 0)
		ft_putstr_fd("exit\n", STD_OUT);
	else
		return (-1);
	return (1);
}
