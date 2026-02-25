/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:45:47 by nd-angel          #+#    #+#             */
/*   Updated: 2026/02/25 19:06:10 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

int    make_redirections(t_redir *redirs)
{
	int		fd;
	
	if (*redirs->type == REDIR_IN)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
}