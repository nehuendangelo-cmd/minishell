/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:19:57 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/08 11:55:24 by nehuen           ###   ########.fr       */
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
