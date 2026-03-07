/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:57 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/07 13:29:50 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *name)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] && ft_strncmp(name, envp[i], ft_strlen(name)) == 0
				&& envp[i][ft_strlen(name)] == '=')
			return (&envp[i][ft_strlen(name) + 1]);
		i++;
	}
	return (NULL);
}
char *get_var_name(char *str)
{
	int		i;
	char	*variable;
	
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		variable[i] = str[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}
int		expanded_len(char *str, t_shell *shell)
{
	int		i;
	char	*variable;
	char 	*value;
	int		len;
	char	*tmp;
	
	len = 0;
	i = 0;
	while (str[i])
	{	
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(shell->last_exit);
			len += ft_strlen(tmp);
			free(tmp);
			i += 2;
		}
		else if (str[i] == '$' && (ft_isalnum(str[i + 1])
		 || str[i + 1] == '_'))
		{
			variable = get_var_name(&str[i + 1]);
			value = get_env_value(shell->envp, variable);
			if (value)
				len += ft_strlen(value);
			i += 1 + ft_strlen(variable);
			free(variable);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char    *expand_string(char *str, t_shell *shell)
{
	int		i;
	char	*variable;
	char 	*value;
	int		len;
	char	*tmp;
	int		j;
	char	*expanded_string;
	
	j = 0;
	len = 0;
	i = 0;
	len = expanded_len(str, shell);
	expanded_string = (malloc(sizeof(char) * (len + 1)));
	i = 0;
	while (str[i])
	{	
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(shell->last_exit);
			ft_memcpy(&expanded_string[j], tmp, ft_strlen(tmp));
			j += ft_strlen(tmp);
			free(tmp);
			i += 2;
		}
		else if (str[i] == '$' && (ft_isalnum(str[i + 1])
		 || str[i + 1] == '_'))
		{
			variable = get_var_name(&str[i + 1]);
			value = get_env_value(shell->envp, variable);
			if (value)
			{
				ft_memcpy(&expanded_string[j], value, ft_strlen(value));
				j += ft_strlen(value);
			}
			i += 1 + ft_strlen(variable);
			free(variable);
		}
		else
		{
			expanded_string[j] = str[i];
			j++;
			i++;
		}
	}
	expanded_string[j] = '\0';
	return (expanded_string);
}

void	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	int		i;

	while(cmd)
	{
		i = 0;
		while (cmd->cmd_and_args[i])
		{
			cmd->cmd_and_args[i] = expand_string(cmd->cmd_and_args[i], shell);
			i++;
		}
		cmd = cmd->next;
	}
}