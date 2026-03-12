/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/12 19:01:06 by nd-angel         ###   ########.fr       */
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
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		/* ancien code: new_envp[i] = envp[i];
		 * problème: copie trop legere , puis free() sur pointeurs non alloués par nous. */
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
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
	struct  sigaction sa;
	sa.sa_handler = signal_handler; //quand sigaction detecte un signal, appelle signal_handler
	sigemptyset(&sa.sa_mask); // ne bloque aucun signal
	sa.sa_flags = 0; // pas de comportemnt special
	sigaction(SIGINT, &sa, NULL);
	(void)argc;
	(void)argv;
	sa.sa_handler = SIG_IGN; // => ignore le signal
	sigaction(SIGQUIT, &sa, NULL); // SIGQUIT (ctrl + \) est ignorer
	shell.envp = ft_copy_env(envp);
	shell.last_exit = 0;
	while (1)
	{
		cmd = NULL;
		line = readline("minishell$");
		if (!line)
			break ;
		if (g_signal == SIGINT)
		{
			shell.last_exit = 130;
			g_signal = 0;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (appel_parse(line, &cmd, &shell) != 0)
		{
			shell.last_exit = 2;
			free(line);
			continue ;
		}
		if (cmd && cmd->cmd_and_args)
			execute(cmd, &shell);
		free_cmds(cmd);
		free(line);
	}
}
