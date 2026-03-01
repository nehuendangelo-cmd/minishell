/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:46:20 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/01 11:47:19 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(char **envp)
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

static void	add_var(char ***envp, char *new_var, int size_envp)
{
	int		i;
	char	**new_envp;
	
	new_envp = malloc(sizeof(char *) * (size_envp + 2));
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
static void	modify_env_without_equal(char ***envp, char *new_var)
{
	int		i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp(new_var, (*envp)[i], (ft_strlen(new_var))) == 0
			&& ((*envp)[i][ft_strlen(new_var)] == '='
			 || (*envp)[i][ft_strlen(new_var)] == '\0'))
				return ;
		i++;	
	}
	add_var(envp, new_var, i);
}
static void	modify_env(char ***envp, char *new_var)
{
	int		i;
	char *eq;
	
  eq = ft_strchr(new_var, '=');
	if (!eq)
		return (modify_env_without_equal(envp, new_var));
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp(new_var, (*envp)[i], (eq - new_var + 1)) == 0)
		{
			(*envp)[i] = new_var;
			return ;
		}
		i++;	
	}
	add_var(envp, new_var, i);
}
void	handle_export(char ***envp, char **cmd)
{
	int		i;

	i = 1;
	if (!cmd[1])
		print_export_env(*envp);
	else
	while (cmd[i])
	{
		modify_env(envp, cmd[i]);
		i++;
	}
}


