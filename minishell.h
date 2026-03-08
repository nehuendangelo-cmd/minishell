/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:39:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/08 00:00:00 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
# include "libft/libft.h"

// token types pour le parsing
typedef enum e_token_type
{
	WORD,
	PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND,
	SINGLE_QUOTE,
	DUBBLE_QUOTE,
	NO_QUOTE
}	t_token_type;

// types de redirections utilises dans t_redir (< > >> <<)
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*prev;
	int				quote_type;
	struct s_token	*next;
}	t_token;

// redirections : < > >> <<
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				pipe_fd[2];
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_and_args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_read_pipe;
	int		*pids_array;
	int		nb_pids;
	int		status;
	char	*here_doc_limiter;
}	t_pipe;

typedef struct s_shell
{
	char	**envp;
	int		last_exit;
}	t_shell;

// ---- parsing ----

int		ft_skip_quote(char *str, int i);
int		ft_op_valid(char *str, int i);
int		ft_syntaxe_op(char *str, int i);
int		ft_ispace(int s);
int		word_is_ok(char c);
int		ft_is_op(char c);

int		ft_quote_expanse(char *str, int i, int *exp);
int		ft_check_quote(char *str, int *err);

int		ft_syntax_error(char *line);
int		ft_check_redirection(char *line);
int		ft_check_pipe(char *line);
int		ft_check_debut_fin(char *line);

char	*ft_shell_substr(const char *s, int start, int len);
char	*ft_strjoin_shell(char *s1, char *s2);
int		ft_string_vide(const char *s);
int		ft_strcmp_shell(const char *s1, const char *s2);

void	ft_add_op_token(t_token **head, char *line, int *i);
void	ft_add_double_op_token(t_token **head, char *line, int *i);
void	ft_add_single_op_token(t_token **head, char *line, int *i);
void	ft_add_word_token(t_token **head, char *line, int *i);
void	ft_add_word_quote_token(t_token **head, char *line, int *i);

t_token	*parse_principal(char *line);

t_cmd	*new_cmd(void);
void	ft_add_arg(t_cmd *cmd, char *word);
void	ft_add_redir(t_cmd *cmd, int type, char *file);
t_cmd	*ft_build_command(t_token *tokens);
t_cmd	*error(char *msg);

void	free_cmds(t_cmd *cmd);
void	free_tokens(t_token *t);
void	free_tab(char **tab);
void	free_redirs(t_redir *redir);

int		is_redirection(int type);
int		is_redirection_prev(t_token *token);
char	*expand_variable(char *str, int *i, char **envp, int last_status);
char	*ft_expand_word(char *str, char **envp, int last_status);
char	*ft_get_env_value(char **envp, char *name);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_charjoin(char *s, char c);
char	*ft_strcpy(char *dest, const char *src);

void	ft_expand_tokens(t_token *tokens, char **envp, int last_status);

// ---- executor ----

void	execute(t_cmd *cmd, t_shell *shell);
int		make_child(pid_t *pid);
int		make_redirections(t_redir *redirs);
char	*find_cmdpath(char *cmd, char **envp);
void	free_paths(char **paths);

void	execute_pipeline(t_cmd *cmd, t_shell *shell);
void	set_first_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void	set_middle_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void	set_last_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void	error_execve_cmd(char *cmd_path, char **cmd_args);
void	error_cmd_path(char **cmd_args);

void	process_heredocs(t_cmd *cmd);
void	handle_heredoc(t_redir *redir);

// ---- builtins ----

int		handle_echo(char **cmd);
int		handle_env(char **envp);
void	handle_exit(char **cmd, int last_exit_code);
int		handle_export(char ***envp, char **cmd);
int		handle_pwd(void);
int		handle_unset(char ***envp, char *cmd);
int		handle_cd(char **cmd, char ***envp);
void	modify_env(char ***envp, char *new_var);
int		is_bultin(t_cmd *cmd, t_shell *shell);

char	*get_env_value(char **envp, char *name);

// ---- signaux ----

extern int	g_signal;
void		signal_handler(int sig);

#endif
