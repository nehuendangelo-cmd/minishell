/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 23:05:40 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/13 11:10:10 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

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

static void	set_heredoc_child(t_redir *redir)
{
	char				*line;

	put_sig_dfl();
	while (1)
	{
		line = readline("heredoc >");
		if (line == NULL)
		{
			close(redir->pipe_fd[1]);
			exit(0);
		}
		if (ft_strncmp(redir->file, line, ft_strlen(redir->file)) == 0)
		{
			free(line);
			close(redir->pipe_fd[1]);
			exit(0);
		}
		write(redir->pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(redir->pipe_fd[1], "\n", 1);
	}
}

void	handle_heredoc(t_redir *redir)
{
	int					pid;
	int					status;

	pipe(redir->pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		put_sig_dfl();
		set_heredoc_child(redir);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(redir->pipe_fd[1]);
	}
}
