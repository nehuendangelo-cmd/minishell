/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:37:08 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/12 21:07:41 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_cmd(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "export", 6) == 0 && cmd_name[6] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "echo", 4) == 0 && cmd_name[4] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0 && cmd_name[3] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "env", 3) == 0 && cmd_name[3] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "cd", 2) == 0 && cmd_name[2] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "unset", 5) == 0 && cmd_name[5] == '\0')
		return (1);
	if (ft_strncmp(cmd_name, "exit", 4) == 0 && cmd_name[4] == '\0')
		return (1);
	return (0);
}

static int	exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!is_builtin_cmd(cmd->cmd_and_args[0]))
		return (0);
	if (!cmd->redirs)
		return (is_bultin(cmd, shell));
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup == -1 || stdout_backup == -1)
		return (is_bultin(cmd, shell));
	if (make_redirections(cmd->redirs) == -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		return (1);
	}
	is_bultin(cmd, shell);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (1);
}

int	is_bultin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd_and_args[0], "export", 6) == 0
		&& cmd->cmd_and_args[0][6] == '\0')
		return (shell->last_exit = handle_export(&shell->envp,
				cmd->cmd_and_args), 1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "echo", 4) == 0
		&& cmd->cmd_and_args[0][4] == '\0')
		return (shell->last_exit = handle_echo(cmd->cmd_and_args), 1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "pwd", 3) == 0
		&& cmd->cmd_and_args[0][3] == '\0')
		return (shell->last_exit = handle_pwd(), 1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "env", 3) == 0
		&& cmd->cmd_and_args[0][3] == '\0')
		return (shell->last_exit = handle_env(shell->envp), 1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "cd", 2) == 0
		&& cmd->cmd_and_args[0][2] == '\0')
		return (shell->last_exit = handle_cd(cmd->cmd_and_args, &shell->envp),
			1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "unset", 5) == 0
		&& cmd->cmd_and_args[0][5] == '\0')
		return (shell->last_exit = handle_unset(&shell->envp,
				cmd->cmd_and_args[1]), 1);
	else if (ft_strncmp(cmd->cmd_and_args[0], "exit", 4) == 0
		&& cmd->cmd_and_args[0][4] == '\0')
		return (handle_exit(cmd->cmd_and_args, shell->last_exit), 1);
	return (shell->last_exit = 0, 0);
}

static void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int					pid;
	char				*cmd_path;
	int					status;

	pid = fork();
	if (pid == 0)
	{
		put_sig_dfl();
		if (make_redirections(cmd->redirs) == -1)
			exit(1);
		cmd_path = find_cmdpath(cmd->cmd_and_args[0], shell->envp);
		if (!cmd_path)
			error_cmd_path(cmd->cmd_and_args);
		execve(cmd_path, cmd->cmd_and_args, shell->envp);
		error_execve_cmd(cmd_path, cmd->cmd_and_args);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	else
		shell->last_exit = 128 + WTERMSIG(status);
}

void	execute(t_cmd *cmd, t_shell *shell)
{
	process_heredocs(cmd);
	if (!cmd->cmd_and_args || !cmd->cmd_and_args[0] || !cmd->cmd_and_args[0][0])
		return ;
	if (!cmd->next && exec_single_builtin(cmd, shell))
		return ;
	if (cmd->next)
		execute_pipeline(cmd, shell);
	else
		execute_single_cmd(cmd, shell);
}
