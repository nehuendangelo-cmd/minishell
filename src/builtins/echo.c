/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:14:34 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/28 20:16:30 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_echo(char **cmd)
{
	int		i;
	int		add_newline;

	
	i = 1;
	add_newline = 1;
	if (cmd[1] && ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
			i++;
		add_newline = 0;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (add_newline == 1)
		write(1, "\n", 1);
}
