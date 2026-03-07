/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:39:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/07 19:03:12 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
# include "libft/libft.h"
#include <readline/history.h>

/*
ce dont j'ai besoin dans la structure pour la partie backend :

-le nom de la commande (exemple : "ls")

- Les arguments de la commande (exmple : "-la" etc commme sur pipex)

- les redirections entrée (les redirections c'est <, <<, >, >>)
- les redirections sorties
- le heredoc 
la commmande suivante
*/




typedef enum e_redir_type
{
    REDIR_IN,       // vaut 0 <
    REDIR_OUT,      // vaut 1 >
    REDIR_APPEND,   // vaut 2 >>
    REDIR_HEREDOC   // vaut 3 <<
}   t_redir_type;


// redirections a gerer pour le mandatory : <, <<, >, >>
typedef struct s_redir
{
	t_redir_type	type; // ecrire directement REDIR_IN ou autre 
	char					*file; //nom du fichier ou delimiteur si here doc
	int							pipe_fd[2];
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		**cmd_and_args;
	t_redir *redirs;

	struct s_cmd *next;
}	t_cmd;

typedef struct s_pipe                                            
{                                                                                                              
    int     pipe_fd[2];                                            
    int     prev_read_pipe;                                                                                     
    int     *pids_array;                                                 
    int     nb_pids;    
		int			status;                                                  
    char    *here_doc_limiter;                                    
}   t_pipe; 

typedef struct s_shell
{
  char    **envp;
  int     last_exit;
} t_shell;
/*
exemple :

commande : cat < in.txt | grep foo > out.txt

t_cmd # 1													t_cmd #2

cmd_and_args : ["cat", NULL]				cmd_and_args : ["grep", "foo", NULL] 
redirs->type = REDIR_IN;						redirs->type = REDIR_OUT
redirs->file = "in.txt"							redirs->file= "out.txt"
redirs->next ------------------->		redir->next = NULL


*/

//fonctions executor
void	execute(t_cmd *cmd, t_shell *shell);
int	make_child(pid_t *pid);
int    make_redirections(t_redir *redirs);
char	*find_cmdpath(char *cmd, char **envp);
void	free_paths(char **paths);
// fin fonctions executor

//fonctions pipes
void	execute_pipeline(t_cmd *cmd, t_shell *shell);

void		set_first_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void		set_middle_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void		set_last_child(t_pipe *p, t_cmd *cmd, t_shell *shell);
void	error_execve_cmd(char *cmd_path, char **cmd_args);
void	error_cmd_path(char **cmd_args);

// heredoc
void	process_heredocs(t_cmd *cmd);
void	handle_heredoc(t_redir *redir);

// fonctions builtin	handle_cd(char **cmd, char **envp);
int	handle_echo(char **cmd);
int	handle_env(char **envp);
void handle_exit(char **cmd, int last_exit_code);
int	handle_export(char ***envp, char **cmd);
int	handle_pwd(void);
int	handle_unset(char ***envp, char *cmd);
int	handle_cd(char **cmd, char ***envp);
void	modify_env(char ***envp, char *new_var);
int		is_bultin(t_cmd *cmd, t_shell *shell);
//fin fonction builtin


//expander
 char    *get_env_value(char **envp, char *name);                                            
 char    *expand_string(char *str, t_shell *shell);
 void    expand_cmd(t_cmd *cmd, t_shell *shell);      

// signals
extern int g_signal;
void	signal_handler(int sig);

  
#endif 