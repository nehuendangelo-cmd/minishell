/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 23:05:40 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/09 16:11:24 by nehuen           ###   ########.fr       */
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
	int		pid;
	struct sigaction	sa;
	int status;
	
	pipe(redir->pipe_fd);
	pid = fork();
	if (pid == 0)	
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
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
	else
	{
		waitpid(pid, &status, 0);
		close(redir->pipe_fd[1]);
	}
}

