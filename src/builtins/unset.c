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

static int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_to_delete(char ***envp, char *cmd, int *size)
{
	int	i;
	int	to_delete;

	i = 0;
	to_delete = -1;
	while ((*envp)[i])
	{
		if (ft_strncmp(cmd, (*envp)[i], (ft_strlen(cmd))) == 0
			&& (*envp)[i][ft_strlen(cmd)] == '=')
			to_delete = i;
		i++;
	}
	*size = i;
	return (to_delete);
}

int	handle_unset(char ***envp, char *cmd)
{
	int		to_delete;
	char	**new_envp;
	int		size;

	if (!cmd)
		return (0);
	if (!is_valid_identifier(cmd))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	to_delete = find_to_delete(envp, cmd, &size);
	if (to_delete == -1)
		return (0);
	new_envp = make_new_envp(size + 1, to_delete, envp);
	*envp = new_envp;
	return (0);
}
