/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:50:40 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/27 19:46:18 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home_env(char **envp, char *path_name)
{
	int		i;
	char	*paths;

	if (!envp ||!envp[0])
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], path_name, ft_strlen(path_name)) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = envp[i];
	if (!paths)
		return (NULL);
	return (paths + ft_strlen(path_name));
}

void	handle_cd(char **cmd, char **envp)
{
	char	*path;
	
	if (!cmd[1])
		path = find_home_env(envp, "HOME=");
	else if (cmd[1][0] == '-' && !cmd[1][1])
		path = find_home_env(envp, "OLDPWD=");
	else 
		path =  cmd[1];
	if (!path)
		return ;
	chdir(path);
}