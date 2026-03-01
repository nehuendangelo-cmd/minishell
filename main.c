/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/01 19:16:54 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static void temp_init_struct(t_cmd *cmd, t_shell *shell, char **envp)
{
	/*
	cmd->cmd_and_args = args;
	cmd->redirs = NULL;
	cmd->next = NULL;
	*/
	(void)cmd;

	shell->envp = ft_copy_env(envp);
	shell->last_exit = 0;
}
int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_shell	*shell;
	(void)argc;
	(void)argv;
	static char *args1[] = {"cd", "/tmp", NULL};
	static char *args2[] = {"pwd", NULL};

	/*
	while (1) 
	{
		line = readline(prompt);
		if (line== NULL)
			break ;
	}
	free(line);
	*/
	cmd = malloc(sizeof(t_cmd));
	shell = malloc(sizeof(t_shell));
	temp_init_struct(cmd, shell, envp);
	cmd->cmd_and_args = args1;
	execute(cmd, shell);
	cmd->cmd_and_args = args2;
	execute(cmd, shell);
	// execute(cmd, shell);
	free(cmd);
	}
