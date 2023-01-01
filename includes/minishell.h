/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:19:06 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/30 00:49:13 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include "libft.h"
# include <signal.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

char	**g_envp;

enum	e_pipe_fd {
	PIPE_READ = 0,
	PIPE_WRITE = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};

enum e_type
{
	E_NULL = 0,
	E_WORD = 1,
	E_REDIR = 2,
	E_PIPE = 3,
	E_CMD = 4,
	E_SIMPLE_CMD = 5
};

typedef struct s_node{
	enum e_type		type;
	char			*str;
	char			**str2;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		count;
}	t_tree;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}	t_index;

/*
	main.c
*/
void		do_minishell(char *s);

/*********************************************/
/**********		tokenizing part		**********/
/*********************************************/
/*
	tokennizer.c
*/
t_tree		*tokenizing(char *s);
void		change_whitespace(char *s);
char		*change_oper(char *s);
char		*change_pipe(char *s, char op);
char		*change_redir(char *s, char op);
/*
	get_env.c
*/
char		**get_env(char **envp);
char		*iterate_env(char *s);
char		*convert_env_to_str(char *env);
char		*get_converted_str(char *s, t_index *i);
char		*get_merged_env_str(char *s, char *env);
/*
	get_env2.c
*/
int			get_env_name_size(char *s);
char		*get_env_name(char *s);
char		*revert_dollar(char *str);
void		check_next_dollar(char *str, int i);
/*
	get_env3.c
*/
char		*free_ret(char *env, char *str);
int			is_iterate(char *s, int double_flag);
/*
	utils.c
*/
int			is_whitespace(char c);
int			check_only_space(char *s);
int			skip_quote(char *s);
int			count_new_space(char *s, char c);
/*
	utils2.c
*/
void		do_change_pipe(char *str, char *s, t_index *idx, char op);
void		do_change_redir(char *str, char *s, t_index *idx, char op);
t_node		*split_str(char *str);
t_node		*make_new(char *str, int size);
void		add_next(t_node *new, t_node *head);
/*
	utils3.c
*/
void		malloc_error(char *s);
char		*ft_strjoin_check_null(char *s1, char *s2);
char		*del_dequote(char **str);
void		do_del_dequote(char *new, char *s, char c, t_index *idx);
int			check_dequote(char *s);

/*********************************************/
/**********		parsing part		**********/
/*********************************************/
/*
	parsing.c
*/
int			parsing(t_tree **tokens);
int			check_type(t_tree *tree, t_tree *tokens, t_node **curr_pipe);
void		parse_error(char *s);
/*
	parsing2.c
*/
t_node		*pop_tokens(t_tree *tree);
int			add_pipe_cmd(t_tree *tree, t_tree *token, t_node *curr);
int			count_wordtype(t_node *node);
int			add_redirect(t_tree *tree, t_tree *tokens, t_node *curr_cmd);
/*
	heredoc.c
*/
int			do_heredoc(char *str, t_node *redir);
char		*create_tmp_file(void);
int			fork_heredoc(char *key, char *tmp_file);
/*
	check_type.c
*/
int			check_alltype(t_tree *tree, t_tree *tokens, t_node *curr_cmd);
int			parse_word(t_tree *tree, t_tree *tokens, \
					t_node *curr_cmd, t_node *curr_tokens);
int			parse_redirect(t_tree *tree, t_tree *tokens, \
					t_node *curr_cmd, t_node *curr_token);
int			parse_pipe(t_tree *tree, t_tree *tokens, t_node **curr_pipe);
/*
	add_simplecmd.c
*/
int			add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd);
void		simcmd_new(t_tree *tokens, t_node *curr_cmd);
void		simcmd_append(t_tree *tokens, t_node *node);

/*****************************************/
/**********		tree_utils		**********/
/*****************************************/
/*
	tree.c
*/
t_node		*create_node(enum e_type type, char *str);
t_tree		*create_tree(void);
void		delete_nodes(t_node *node);
void		delete_tree(t_tree *tree);
void		delete_str(t_node *node);
/*********************************************/
/**********		executor part		**********/
/*********************************************/
/*
	executor.c
*/
int			executor(t_tree *tree);
char		**get_path(char **list);
pid_t		*init_pids(t_tree *tree);
void		free_path(char **path);
/*
	executor_utils.c
*/
int			init_fd(int **fd);
void		ft_close(int fd);
int			iterate_statloc(int statloc);
/*
	redirection.c
*/
int			*set_redirection(t_node *node, int *fd);
int			do_redirect(t_node *node, int *fd);
/*
	set_redirection.c
*/
int			check_redirection_type(t_node *node, int *fd);
void		redirection_in(t_node *node, int *fd);
void		redirection_out(t_node *node, int *fd);
void		redirection_append(t_node *node, int *fd);
void		redirection_heredoc(t_node *node, int *fd);
/*
	run_builtin.c
*/
int			run_builtin(t_node *sim_cmd, int *fd);
int			nopipe_builtin(t_tree *tree);
int			is_builtin(t_node *sim_cmd);
/*
	error.c
*/
int			print_errno(int fd, char *s1, char *s2, int ret);
int			print_error(int fd, char *s1, char *s2, int ret);
int			find_errno(void);

/*
	fork.c
*/
pid_t		*fork_shell(t_node *pipe, char **path, pid_t *pids);
void		set_pipe_write(t_node *node, int *pipe_fd, int *fd);
void		set_pipe_read(t_node *node, int *pipe_fd, int *fd);
int			wait_child(int *pids);
/*
	execute_cmd.c
*/
int			execute_cmd(t_node *cmd, int *fd, char **path);
void		execute_simcmd(t_node *node, char **path);
char		*find_path(char *cmd, char **path);

/*********************************************/
/**********		builtin part		**********/
/*********************************************/
/*
	builtin_utils.c
*/
char		**malloc_env(int size);
t_index		*make_idx(void);
void		free_env(char **s);
/*
	builtin_utils2.c
*/
char		*safe_ft_strjoin(char *s1, char *s2, char *s3);
char		*safe_ft_strdup(char *s1, char *s2);
char		*safe_ft_substr(char *s1, int start, int size, char *s2);
void		*safe_ft_calloc(size_t count, size_t size, char *s);
/*
	do_cd.c
*/
int			do_cd(char **str, int *fd);
/*
	do_cd2.c
*/
void		free_both(char *cur_dir, char *next_dir);
int			print_cd_erro_msg(int *fd, char *str);
char		*remove_oldpwd(char *str, int *flag);
void		set_pwd_env(char *cur_dir, char *next_dir);
/*
	do_echo.c
*/
int			do_echo(char **str, int *fd);
/*
	do_env.c
*/
int			do_env(int *fd);
int			is_equal(char *s);
/*
	do_exit.c
*/
int			do_exit(char **str, int *fd);
int			print_exit_message(int *fd, int flag, char *str);
/*
	do_exit2.c
*/
long long	ft_atoll(const char *str, int *flag);
/*
	do_export.c
*/
int			do_export(char **cmd, int *fd);
void		print_export(int *fd);
char		**sorted_env(void);
char		**export_env(char *s);
int			envp_size(void);
/*
	do_export2.c
*/
char		**change_env(char *s, char **ret, int i);
int			dup_export(char *s, char *env);
/*
	do_pwd.c
*/
int			do_pwd(int *fd);
/*
	do_unset.c
*/
int			do_unset(char **sim_cmd, int *fd);
void		unset_envp_list(t_index *idx);
int			check_environ(char *word, int *fd, int is_export);
int			error_unset_export(char *command, char *str, char *word, int *fd);
int			check_dup(char *s, char *env);
/*********************************************/
/**********		  signal part		**********/
/*********************************************/
/*
	signal.c
*/
void		main_signal(void);
void		fork_signal(void);
void		origin_signal(void);
void		int_hanlder(int sig);
void		modify_exit_status(int n);
void		echoctl_off(void);
void		echoctl_on(void);
void		eof_handler(void);
void		quit_by_signal(int status);
void		heredoc_signal(void);
void		sigint_heredoc(int sig);

#endif
