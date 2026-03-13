/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/13 12:12:54 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

static void	process_line(char *line, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = NULL;
	add_history(line);
	if (appel_parse(line, &cmd, shell) != 0)
	{
		shell->last_exit = 2;
		free(line);
		return ;
	}
	if (cmd && cmd->cmd_and_args)
		execute(cmd, shell);
	free_cmds(cmd);
	free(line);
}

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_signal == SIGINT)
			update_g_signal(shell);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		process_line(line, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	set_signal();
	(void)argc;
	(void)argv;
	shell.envp = ft_copy_env(envp);
	shell.last_exit = 0;
	main_loop(&shell);
}
