# **************************************************************************** #
#                                PARSING MINISHELL                             #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

INC_DIR     = .
SRC_DIR     = src
PARS_DIR    = src/parsing
LIBFT_DIR   = src/libft
LIBFT       = $(LIBFT_DIR)/libft.a

OBJ_DIR     = objs

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

PARS_SRCS = \
	build.c \
	char.c \
	free.c \
	main.c \
	missing.c \
	parse.c \
	quote.c \
	string.c \
	syntaxe.c \
	tok2.c \
	token.c \
	utils.c

SRCS = $(addprefix $(PARS_DIR)/, $(PARS_SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(PARS_SRCS:.c=.o))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
