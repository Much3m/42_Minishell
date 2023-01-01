/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:10:10 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/29 22:25:15 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;

	if (argc != 1)
		return (print_error(STD_ERROR, \
			"No arguments are required for execution.", NULL, -1));
	(void)argv;
	g_envp = get_env(envp);
	while (1)
	{
		main_signal();
		str = readline("minishell $ ");
		if (str != NULL)
		{
			do_minishell(str);
			free(str);
			continue ;
		}
		eof_handler();
		break ;
	}
	echoctl_on();
	exit(ft_atoi(g_envp[0]));
}

void	do_minishell(char *s)
{
	t_tree	*tree;
	int		exit_status;

	if (check_only_space(s))
		;
	else if (s[0] != '\0')
	{
		add_history(s);
		tree = tokenizing(s);
		if (tree == NULL)
			exit_status = 0;
		else
		{
			exit_status = parsing(&tree);
			if (exit_status == 0)
				exit_status = executor(tree);
		}
		if (tree)
			delete_tree(tree);
		modify_exit_status(exit_status);
	}
}
