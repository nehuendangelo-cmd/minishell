/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 23:05:40 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/04 14:47:56 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredocs(t_cmd *cmd)
{
	t_redir *redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				handle_heredoc(redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	handle_heredoc(t_redir *redir)
{
	char *line;
	
	pipe(redir->pipe_fd);
	while (1)
	{
		line = readline("heredoc >");
		if (ft_strncmp(redir->file, line, ft_strlen(redir->file)) == 0)
		{
			free(line);
			close(redir->pipe_fd[1]);
			break;
		}
		write(redir->pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(redir->pipe_fd[1], "\n", 1);
	}
}
