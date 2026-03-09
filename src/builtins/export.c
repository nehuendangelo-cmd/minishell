/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:46:20 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/09 18:47:28 by nehuen           ###   ########.fr       */
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
	/* ancien code: new_envp[i] = new_var;
	 * problème: new_var pointe vers cmd[i], libéré après la commande. */
	new_envp[i] = ft_strdup(new_var);
	if (!new_envp[i])
	{
		free(new_envp);
		return ;
	}
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
 void	modify_env(char ***envp, char *new_var)
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
			char	*dup_var;

			/* ancien code: (*envp)[i] = new_var;
			 * problème: pointeur temporaire venant de cmd. */
			dup_var = ft_strdup(new_var);
			if (!dup_var)
				return ;
			free((*envp)[i]);
			(*envp)[i] = dup_var;
			return ;
		}
		i++;	
	}
	add_var(envp, new_var, i);
}
static int	is_valid_var_name(char *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	if (ft_isalpha(cmd[0]) || cmd[0] == '_')
	{
		while (cmd[i] && cmd[i] != '=')
		{
			if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}
int	handle_export(char ***envp, char **cmd)
{
	int		i;

	i = 1;
	if (!cmd[1])
		print_export_env(*envp);
	else
	while (cmd[i])
	{
		if (!is_valid_var_name(cmd[i]))
		{
			ft_putstr_fd("bash: export: ", 2);
 			ft_putstr_fd(cmd[i], 2);
 			ft_putendl_fd(": not a valid identifier", 2);
			return (1);
		}
		modify_env(envp, cmd[i]);
		i++;
	}
	return (0);
}


