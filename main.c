/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/07 20:34:04 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 int g_signal = 0;
 
static char **ft_copy_env(char **envp)
{
	char **new_envp;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd		*cmd;
	char		*line;
	
	;
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	shell.envp = ft_copy_env(envp);
	shell.last_exit = 0;
	(void)shell;
	while (1)
	{
		cmd = NULL;
		line = readline("minishell$");
		if (!line)
			break ;
		if (line[0] == '\0')                                                  
		{               
			free(line);                                                       
			continue ;                                                        
		}
		add_history(line);
		if (appel_parse(line, &cmd) != 0)
		{
			free(line);
			continue ;
		}
		//execute(cmd, shell);
		free_cmds(cmd);
		free(line);
	}
}
