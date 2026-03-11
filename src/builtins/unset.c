/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:09:27 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/11 16:52:51 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_new_envp(int size, int to_delete, char ***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (size));
	if (!new_envp)
		return (NULL);
	while ((*envp)[i])
	{
		if (i != to_delete)
			new_envp[j++] = (*envp)[i];
		i++;
	}
	new_envp[j] = NULL;
	free(*envp);
	return (new_envp);
}

int	handle_unset(char ***envp, char *cmd)
{
	int		i;
	char	**new_envp;
	int		to_delete;

	if (!cmd)
		return (0);
	i = 0;
	to_delete = -1;
	while ((*envp)[i])
	{
		if (ft_strncmp(cmd, (*envp)[i], (ft_strlen(cmd))) == 0
			&& (*envp)[i][ft_strlen(cmd)] == '=')
			to_delete = i;
		i++;
	}
	if (to_delete == -1)
		return (0);
	new_envp = make_new_envp(i + 1, to_delete, envp);
	*envp = new_envp;
	return (0);
}
