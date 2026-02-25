/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:45:47 by nd-angel          #+#    #+#             */
/*   Updated: 2026/02/25 21:12:43 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    make_redirections(t_redir *redirs)
{
	int		fd;
	
	while (redirs)
	{
		fd = -1;
		if (redirs->type == REDIR_IN)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd == -1)
			return (perror("Error opening infile"), -1);
			dup2(fd, STDIN_FILENO);
		}
		if (redirs->type == REDIR_OUT)
		{
			fd = open(redirs->file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if (fd == -1)
				return (perror("Error opening infile"), -1);
			dup2(fd, STDOUT_FILENO);
		}
		if (redirs->type == REDIR_APPEND)
		{
			fd = open(redirs->file, O_WRONLY|O_CREAT|O_APPEND, 0644);
			if (fd == -1)
				return (perror("Error opening infile"), -1);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		redirs = redirs->next;
	}
	return (0);
}
