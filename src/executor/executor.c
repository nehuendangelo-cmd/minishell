/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:37:08 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/01 11:44:05 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_bultin(t_cmd *cmd, t_shell *shell)
{
	if (strncmp(cmd->cmd_and_args[0], "export", 6) == 0
	&& cmd->cmd_and_args[0][6] == '\0')
		return (handle_export(&shell->envp, cmd->cmd_and_args), 1);
	else if (strncmp(cmd->cmd_and_args[0], "echo", 4) == 0
	&& cmd->cmd_and_args[0][4] == '\0')
		return (handle_echo(cmd->cmd_and_args), 1);
	else if (strncmp(cmd->cmd_and_args[0], "pwd", 3) == 0
	&& cmd->cmd_and_args[0][3] == '\0')
		return (handle_pwd(), 1);
	else if (strncmp(cmd->cmd_and_args[0], "env", 3) == 0
	&& cmd->cmd_and_args[0][3] == '\0')
		return (handle_env(shell->envp), 1);
	else if (strncmp(cmd->cmd_and_args[0], "cd", 2) == 0
	&& cmd->cmd_and_args[0][2] == '\0')
		return (handle_cd(cmd->cmd_and_args, shell->envp), 1);
	else if (strncmp(cmd->cmd_and_args[0], "unset", 5) == 0
	&& cmd->cmd_and_args[0][5] == '\0')
		return (handle_unset(&shell->envp, cmd->cmd_and_args[1]), 1);
	else if (strncmp(cmd->cmd_and_args[0], "exit", 4) == 0
	&& cmd->cmd_and_args[0][4] == '\0')
		return (handle_exit(cmd->cmd_and_args, shell->last_exit), 1);
	else
		return (0);
}
void	execute(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (is_bultin(cmd, shell))
		return ;
	if (make_child(&pid) == -1)
		return ;
	if (pid == 0)
		set_child(cmd, shell->envp);
	waitpid(pid, &status, 0);
}