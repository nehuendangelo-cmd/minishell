/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/08 15:45:25 by nehuen           ###   ########.fr       */
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
	char		*line;
	struct  sigaction sa;
	
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	(void)argc;
	(void)argv;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	shell.envp = ft_copy_env(envp);
	shell.last_exit = 0;
	(void)shell;
	while (1)
	{
		line = readline("minishell$");
		if (!line)
			break ;
		if (line[0] == '\0')                                                  
		{               
			free(line);                                                       
			continue ;                                                        
		}
		add_history(line);
		//parse(line, cmd);
		//execute(cmd, shell);
		free(line);
	}
}
