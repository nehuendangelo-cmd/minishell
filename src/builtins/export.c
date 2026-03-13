/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:46:20 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/12 22:16:58 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(char ***envp, char *new_var, int size_envp)
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

void	modify_env_without_equal(char ***envp, char *new_var)
{
	int	i;

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
	char	*eq;
	char	*dup_var;

	eq = ft_strchr(new_var, '=');
	if (!eq)
		return (modify_env_without_equal(envp, new_var));
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp(new_var, (*envp)[i], (eq - new_var + 1)) == 0)
		{
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

int	is_valid_var_name(char *cmd)
{
	int	i;

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
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!cmd[1])
		print_export_env(*envp);
	else
	{
		while (cmd[i])
		{
			if (!is_valid_var_name(cmd[i]))
			{
				ft_putstr_fd("bash: export: ", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd(": not a valid identifier", 2);
				ret = 1;
			}
			else
				modify_env(envp, cmd[i]);
			i++;
		}
	}
	return (ret);
}
