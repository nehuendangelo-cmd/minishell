/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:14:34 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/02 16:43:32 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_n_flag(char *cmd)
{
	int		y;

	y = 0;
	if (cmd && ft_strncmp(cmd, "-n", 2) == 0)
	{
		y++;
		while (cmd[y] == 'n')
			y++;
		if (cmd[y])
			return (0);
		else 
			return (1);
	}
	else
		return (0);
}
int	handle_echo(char **cmd)
{
	int		i;
	int		add_newline;

	i = 1;
	add_newline = 1;
	while (cmd[i])
	{
		if (is_valid_n_flag(cmd[i]))
		{
			add_newline = 0;
			i++;
		}
		else
			break;
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
	return (0);
}
