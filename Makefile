# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 16:01:44 by nehuen            #+#    #+#              #
#    Updated: 2026/03/08 00:00:00 by nehuen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -I. -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

SRCS = main.c \
	src/executor/executor.c \
	src/executor/make.child.c \
	src/executor/path.c \
	src/executor/expander.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/handle_pwd.c \
	src/builtins/unset.c \
	src/pipes/pipes.c \
	src/pipes/set_childs.c \
	src/redirections/heredoc.c \
	src/redirections/redirections.c \
	src/signals.c \
	src/parsing/build.c \
	src/parsing/free.c \
	src/parsing/missing.c \
	src/parsing/parse.c \
	src/parsing/quote.c \
	src/parsing/string.c \
	src/parsing/syntaxe.c \
	src/parsing/tok2.c \
	src/parsing/token.c \
	src/parsing/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C ./libft

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
