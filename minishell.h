/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:39:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/24 15:39:32 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "src/libft/libft.h"

//*********************************************************************************
//*                                                                               *
//*                             PART PARSING                                      *
//*                                                                               *
//*********************************************************************************

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HEREDOC,
    APPEND,
    SINGLE_QUOTE,
    DUBBLE_QUOTE,
    NO_QUOTE
} t_token_type;

typedef enum e_redir_type
{
    REDIR_APPEND_TYPE,
    REDIR_HEREDOC_TYPE
}   t_redir_type;

typedef struct s_token
{
    char *value;
    t_token_type type;
    struct s_token *prev;
    int quote_type;
    struct s_token *next;
} t_token;

// redirections a gerer pour le mandatory : <, <<, >, >>
typedef struct s_redir
{
	t_redir_type	type;
	char			*file; //nom du fichier ou delimiteur si here doc
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		**cmd_and_args;
	t_redir *redirs;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_dir
{
    char            *name;
    char            *value;
    struct s_dir    *next;
}   t_dir;

// char.c
int ft_skip_quote(char *str, int i);
int ft_op_valid(char *str, int i);
int	ft_syntaxe_op(char *str, int i);
int	ft_ispace(int s);
int word_is_ok(char c);
int ft_is_op(char c);

// quote.c
int ft_quote_expanse(char *str, int i, int *exp);
int ft_check_quote(char *str, int *err);

// syntaxe.c
int ft_syntax_error(char *line);
int ft_check_redirection(char *line);
int ft_check_pipe(char *line);
int ft_check_debut_fin(char *line);

// string.c
char *ft_shell_substr(const char *s, int start, int len);
char *ft_strjoin_shell(char *s1, char *s2);
int ft_string_vide(const char *s);
int ft_strcmp_shell(const char *s1, const char *s2);

// token.c
void ft_add_op_token(t_token **head, char *line, int *i);
void ft_add_double_op_token(t_token **head, char *line, int *i);
void ft_add_single_op_token(t_token **head, char *line, int *i);
void ft_add_word_token(t_token **head, char *line, int *i);
void ft_add_word_quote_token(t_token **head, char *line, int *i);

// parse.c
t_token *parse_principal(char *line);

// build.c
t_cmd *new_cmd(void);
void ft_add_arg(t_cmd *cmd, char *word);
void ft_add_redir(t_cmd *cmd, int type, char *file);
t_cmd *ft_build_command(t_token *tokens);
t_cmd *error(char *msg);

// free.c
void free_cmds(t_cmd *cmd);
void free_tokens(t_token *t);
void free_tab(char **tab);
void free_redirs(t_redir *redir);

// utils.c
int is_redirection(int type);
int is_redirection_prev(t_token *token);
char *expand_variable(char *str, int *i, t_env *env, int last_status);
char *ft_expand_word(char *str, t_env *env, int last_status);
char *ft_get_env_value(t_env *env, char *name);
char *ft_strjoin_free(char *s1, char *s2);
char *ft_charjoin(char *s, char c);
char *ft_strcpy(char *dest, const char *src);

// tok2.c
void ft_expand_tokens(t_token *tokens, t_env *env, int last_status);

#endif