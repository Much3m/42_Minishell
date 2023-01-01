# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 14:55:09 by seowokim          #+#    #+#              #
#    Updated: 2023/01/01 21:19:39 by min-skim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
NAME_D			=	d_minisehll

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
DEBUG			=	-fsanitize=address

# READLINE_LIB	=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib
# READLINE_INC	=	-I/Users/$(USER)/.brew/opt/readline/include

READLINE_LIB	= -lreadline -L/usr/local/opt/readline/lib
READLINE_INC	= -I/usr/local/opt/readline/include

LIB_DIR			=	./libft
HEADER			=	./includes
INCLUDES		=	-I$(HEADER) -I$(LIB_DIR)

SRC			=	./srcs/main.c

EXEC			=	./srcs/tree/tree.c \
					./srcs/executor/error.c \
					./srcs/executor/executor_utils.c \
					./srcs/executor/executor.c \
					./srcs/executor/redirection.c \
					./srcs/executor/set_redirection.c \
					./srcs/executor/run_builtin.c \
					./srcs/executor/fork.c \
					./srcs/executor/execute_cmd.c \

TOKEN			=	./srcs/tokenizer/tokenizer.c \
					./srcs/tokenizer/get_env.c \
					./srcs/tokenizer/get_env2.c \
					./srcs/tokenizer/get_env3.c \
					./srcs/tokenizer/utils.c \
					./srcs/tokenizer/utils2.c \
					./srcs/tokenizer/utils3.c

BUILTIN			=	./srcs/builtin/builtin_utils.c \
					./srcs/builtin/builtin_utils2.c \
					./srcs/builtin/do_pwd.c \
					./srcs/builtin/do_echo.c \
					./srcs/builtin/do_exit.c \
					./srcs/builtin/do_exit2.c \
					./srcs/builtin/do_cd.c \
					./srcs/builtin/do_cd2.c \
					./srcs/builtin/do_env.c \
					./srcs/builtin/do_export.c \
					./srcs/builtin/do_export2.c \
					./srcs/builtin/do_unset.c \

PARSER			=	./srcs/parser/add_simplecmd.c \
					./srcs/parser/check_type.c \
					./srcs/parser/parser.c \
					./srcs/parser/parser2.c \
					./srcs/parser/heredoc.c \

SIGNAL			=	./srcs/signal/signal.c \
					./srcs/signal/signal2.c \

SRCS			= $(SRC) $(EXEC) $(TOKEN) $(BUILTIN) $(PARSER) $(SIGNAL)

OBJS			= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -o $@ -c $<

$(NAME):		$(OBJS)
				make -C $(LIB_DIR)
				$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_LIB) $(READLINE_INC) -L $(LIB_DIR) -lft -o $(NAME) $(OBJS)

all:			$(NAME)

clean:
				make -C $(LIB_DIR) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(LIB_DIR) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			clean fclean all re
