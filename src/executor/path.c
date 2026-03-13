/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:35:54 by nd-angel          #+#    #+#             */
/*   Updated: 2026/03/13 12:44:15 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access_file(char *cmd_path);

void	free_paths(char **paths)
{
	int		i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**find_path_env(char **envp)
{
	int		i;
	char	**paths;

	if (!envp || !envp[0])
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*make_valid_cmd_path(char *paths, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(paths, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static int	check_access_file(char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd_path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		ft_putstr_fd(cmd_path, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	return (0);
}

char	*find_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		check_access_file(cmd);
		return (ft_strdup(cmd));
	}
	paths = find_path_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = make_valid_cmd_path(paths[i], cmd);
		if (full_path)
			return (free_paths(paths), full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
