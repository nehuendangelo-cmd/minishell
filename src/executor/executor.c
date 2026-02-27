/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:37:08 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/27 14:59:40 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	
	if (make_child(&pid) == -1)
		return ;
	if (pid == 0)
		set_child(cmd, envp);
	waitpid(pid, &status, 0);
}