/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:35:36 by nd-angel          #+#    #+#             */
/*   Updated: 2026/03/13 12:27:53 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bultin2(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->cmd_and_args[0];
	if (ft_strncmp(name, "cd", 2) == 0 && name[2] == '\0')
		return (shell->last_exit = handle_cd(cmd->cmd_and_args,
				&shell->envp), 1);
	if (ft_strncmp(name, "unset", 5) == 0 && name[5] == '\0')
		return (shell->last_exit = handle_unset(&shell->envp,
				cmd->cmd_and_args), 1);
	if (ft_strncmp(name, "exit", 4) == 0 && name[4] == '\0')
		return (shell->last_exit = handle_exit(cmd->cmd_and_args,
				shell->last_exit), 1);
	return (shell->last_exit = 0, 0);
}

int	is_bultin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->cmd_and_args[0];
	if (ft_strncmp(name, "export", 6) == 0 && name[6] == '\0')
		return (shell->last_exit = handle_export(&shell->envp,
				cmd->cmd_and_args), 1);
	if (ft_strncmp(name, "echo", 4) == 0 && name[4] == '\0')
		return (shell->last_exit = handle_echo(cmd->cmd_and_args), 1);
	if (ft_strncmp(name, "pwd", 3) == 0 && name[3] == '\0')
		return (shell->last_exit = handle_pwd(), 1);
	if (ft_strncmp(name, "env", 3) == 0 && name[3] == '\0')
		return (shell->last_exit = handle_env(shell->envp), 1);
	return (is_bultin2(cmd, shell));
}

void	restore_fds(int stdin_bak, int stdout_bak)
{
	dup2(stdin_bak, STDIN_FILENO);
	dup2(stdout_bak, STDOUT_FILENO);
	close(stdin_bak);
	close(stdout_bak);
}

void	apply_redirs_only(t_redir *redirs)
{
	int	stdin_bak;
	int	stdout_bak;

	stdin_bak = dup(STDIN_FILENO);
	stdout_bak = dup(STDOUT_FILENO);
	make_redirections(redirs);
	restore_fds(stdin_bak, stdout_bak);
}

int	ft_cmd_count(t_cmd *cmd)
{
	t_cmd	*count;
	int		i;

	i = 0;
	count = cmd;
	while (count)
	{
		count = count->next;
		i++;
	}
	return (i);
}
