# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/26 16:01:44 by nehuen            #+#    #+#              #
#    Updated: 2026/02/26 16:16:23 by nehuen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -I. -Wall -Wextra -Werror

LIBFT = ./libft/libft.a


# GNL = ./GNL/get_next_line.a
# GNL_DIR = ./GNL/

SRCS = src/executor/executor.c \
		 src/executor/make.child.c \
		 src/executor/path.c \
		 src/executor/redirections.c \
		 main.c \
		 
			 
OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline


all: $(NAME) $(LIBFT) $(OBJS)

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
