/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:46:20 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/27 20:46:42 by nehuen           ###   ########.fr       */
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

void	modify_env(char ***envp, char *new_var)
{
	int		i;
	char **new_envp;
	char *eq;
	
  eq = ft_strchr(new_var, '=');
	if (!eq)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp(new_var, (*envp)[i], eq - new_var) == 0)
		{
			(*envp)[i] = new_var;
			return ;
		}
		i++;	
	}
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}
void	handle_export(char ***envp, char **cmd)
{
	if (!cmd[1])
		print_export_env(*envp);
	else
		modify_env(envp, cmd[1]);
}