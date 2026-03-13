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

static char	*read_line_non_interactive(void)
{
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (isatty(fileno(stdin)))
			line = readline("minishell$ ");
		else
			line = read_line_non_interactive();
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
	return (shell.last_exit);
}
