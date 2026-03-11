/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:10:41 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/11 16:15:58 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(char **envp)
{
	int		i;
	int		y;
	int		flag;

	i = 0;
	while (envp[i])
	{
		y = 0;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (envp[i][y])
		{
			ft_putchar_fd(envp[i][y], 1);
			if (envp[i][y] == '=')
			{
				ft_putchar_fd('"', 1);
				flag = 1;
			}
			if (!envp[i][y + 1] && flag == 1)
				ft_putchar_fd('"', 1);
			y++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}