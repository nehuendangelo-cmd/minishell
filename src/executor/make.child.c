/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:17:22 by nd-angel          #+#    #+#             */
/*   Updated: 2026/02/26 15:51:39 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_child(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("error creating child");
		return (-1);
	}
	return (0);
}

int	set_child(t_cmd *cmd, char **envp)
{
	char	*cmd_path;
	if (make_redirections(cmd->redirs) == -1)
		exit(1);
	cmd_path = find_cmdpath(cmd->cmd_and_args[0], envp);
	if (cmd_path == NULL)
	{
		ft_putstr_fd(cmd->cmd_and_args[0], 2);
    ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, cmd->cmd_and_args, envp);
	free(cmd_path);
	perror(cmd->cmd_and_args[0]);
	exit(127);
}
