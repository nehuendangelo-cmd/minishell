# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 16:01:44 by nehuen            #+#    #+#              #
#    Updated: 2026/03/12 18:42:04 by nd-angel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -I. -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

LIBFT = ./libft/libft.a

SRCS = main.c \
	src/executor/executor.c \
	src/executor/path.c \
	src/executor/expander.c \
	src/executor/pipeline.c \
	src/executor/set_childs.c \
	src/executor/utils.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/export.c \
	src/builtins/export2.c \
	src/builtins/handle_pwd.c \
	src/builtins/unset.c \
	src/redirections/heredoc.c \
	src/redirections/redirections.c \
	src/signals.c \
	src/parsing/char.c \
	src/parsing/build.c \
	src/parsing/free.c \
	src/parsing/missing.c \
	src/parsing/parse.c \
	src/parsing/quote.c \
	src/parsing/string.c \
	src/parsing/syntaxe.c \
	src/parsing/tok2.c \
	src/parsing/token.c \
	src/parsing/utils2.c \
	src/parsing/utils.c

OBJS = $(SRCS:.c=.o)
VALGRIND = valgrind
VG_FLAGS = --leak-check=full --show-leak-kinds=definite --track-origins=yes --show-reachable=no


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L/opt/homebrew/opt/readline/lib -lreadline

$(LIBFT):
	make -C ./libft

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	$(VALGRIND) $(VG_FLAGS) ./$(NAME)

valgrind_clean: $(NAME)
	$(VALGRIND) $(VG_FLAGS) ./$(NAME) 2>&1 | grep -v "still reachable"

.PHONY: all clean fclean re valgrind valgrind_clean




