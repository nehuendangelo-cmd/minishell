/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:11:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/11 16:10:06 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(char **cmd, int last_exit_code)
{
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": too many arguments", 2);
			return (1);
		}
		if (ft_is_numeric_str(cmd[1]))
			exit(ft_atoi(cmd[1]));
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
	}
	else
		exit(last_exit_code);
	return (0);
}
