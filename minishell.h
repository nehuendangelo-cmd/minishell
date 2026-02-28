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

typedef enum e_redir_type
{
    REDIR_IN,       // vaut 0
    REDIR_OUT,      // vaut 1
    REDIR_APPEND,   // vaut 2
    REDIR_HEREDOC   // vaut 3
}   t_redir_type;


// redirections a gerer pour le mandatory : <, <<, >, >>
typedef struct s_redir
{
	t_redir_type	type; // ecrire directement REDIR_IN ou autre 
	char					*file; //nom du fichier ou delimiteur si here doc
	struct s_redir	*next;
}	t_redir;


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
    APPEND
} t_token_type;

typedef struct s_token
{
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;



int ft_skip_quote(char *str, int i);
int ft_op_valid(char *str, int i);
int	ft_syntaxe_op(char *str, int i);
int	ft_ispace(int s);
int word_is_ok(char c);
int ft_syntax_error(char *line);
int ft_check_quote(char *str, int *err);
int ft_quote_expanse(char *str, int i, int *exp);
int ft_check_quote(char *str, int *err);
void ft_add_word_token(t_token **head, char *line, int *i);
t_token *parse_principal(char *line);
void ft_add_op_token(t_token **head, char *line, int *i);
void ft_add_single_op_token(t_token **head, char *line, int *i);
void ft_add_word_token(t_token **head, char *line, int *i);
void ft_add_double_op_token(t_token **head, char *line, int *i);
int ft_check_redirection(char *line);
int ft_check_pipe(char *line);
int ft_check_debut_fin(char *line);
char *ft_shell_substr(const char *s, int start, int len);
char *ft_strjoin_shell(char *s1, char *s2);
int ft_string_vide(const char *s);
int ft_strcmp_shell(const char *s1, const char *s2);

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

#endif