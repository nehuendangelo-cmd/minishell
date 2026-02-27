/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:07:05 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/27 14:58:46 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void temp_init_struct(t_cmd *cmd)
{
	static char *args[] = {"./main.c", NULL};
	
	cmd->cmd_and_args = args;
	
	cmd->redirs = NULL;
	cmd->next = NULL;
}
int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	
	(void)argc;
	(void)argv;


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
	temp_init_struct(cmd);
	execute(cmd, envp);
	free(cmd);
	}
