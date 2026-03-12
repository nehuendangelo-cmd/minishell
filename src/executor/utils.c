/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:35:36 by nd-angel          #+#    #+#             */
/*   Updated: 2026/03/12 21:06:52 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	put_sig_dfl(void)
{
	struct sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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