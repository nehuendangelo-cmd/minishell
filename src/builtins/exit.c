/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:11:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/27 16:21:45 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_exit(char **cmd, int last_exit_code)
{
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putendl_fd("erreur", 2);
			return ;
		}
		exit(ft_atoi(cmd[1]));
	}
	else 
		exit(last_exit_code);
}