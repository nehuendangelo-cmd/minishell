/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_childs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:34:23 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/05 15:54:16 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	error_cmd_path(char **cmd_args)
{
	perror("cmd1 introuvable");
	free_paths(cmd_args);
	exit(127);
}
void	error_execve_cmd(char *cmd_path, char **cmd_args)
{
	free_paths(cmd_args);
	free(cmd_path);
	perror("execve cmd failed");
	exit(127);
}

void		set_first_child(t_pipe *p, t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	
	dup2(p->pipe_fd[1], 1);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	free(p->pids_array);
	make_redirections(cmd->redirs);
	if (is_bultin(cmd, shell))
    exit(shell->last_exit);
	cmd_path = find_cmdpath(cmd->cmd_and_args[0], shell->envp);
	if (!cmd_path)
		error_cmd_path(cmd->cmd_and_args);
	execve(cmd_path, cmd->cmd_and_args, shell->envp);
	error_execve_cmd(cmd_path, cmd->cmd_and_args);
}

void		set_middle_child(t_pipe *p, t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	dup2(p->prev_read_pipe, 0);
	dup2(p->pipe_fd[1], 1);
	close(p->prev_read_pipe);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	free(p->pids_array);
	make_redirections(cmd->redirs);
	if (is_bultin(cmd, shell))
    exit(shell->last_exit);
	cmd_path = find_cmdpath(cmd->cmd_and_args[0], shell->envp);
	if (!cmd_path)
		error_cmd_path(cmd->cmd_and_args);
	execve(cmd_path, cmd->cmd_and_args, shell->envp);
	error_execve_cmd(cmd_path, cmd->cmd_and_args);
}
void		set_last_child(t_pipe *p, t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	dup2(p->prev_read_pipe, 0);
	close(p->prev_read_pipe);
	free(p->pids_array);
	make_redirections(cmd->redirs);
	if (is_bultin(cmd, shell))
    exit(shell->last_exit);
	cmd_path = find_cmdpath(cmd->cmd_and_args[0], shell->envp);
	if (!cmd_path)
		error_cmd_path(cmd->cmd_and_args);
	execve(cmd_path, cmd->cmd_and_args, shell->envp);
	error_execve_cmd(cmd_path, cmd->cmd_and_args);
}
