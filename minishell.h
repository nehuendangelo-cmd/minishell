/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:39:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/26 16:14:16 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
# include "libft/libft.h"

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

typedef struct s_cmd
{
	char		**cmd_and_args;
	t_redir *redirs;
	struct s_cmd *next;
}	t_cmd;


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
void	execute(t_cmd *cmd, char **envp);
int	make_child(pid_t *pid);
int	set_child(t_cmd *cmd, char **envp);
int    make_redirections(t_redir *redirs);
char	*find_cmdpath(char *cmd, char **envp);
// fin fonctions executor

#endif 