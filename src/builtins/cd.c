/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:50:40 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/12 22:41:31 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home_env(char **envp, char *path_name)
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

static char	*find_path(char **cmd, char ***envp)
{
	char	*path;

	if (!cmd[1])
		path = find_home_env(*envp, "HOME=");
	else if (cmd[1][0] == '-' && !cmd[1][1])
		path = find_home_env(*envp, "OLDPWD=");
	else
		path = cmd[1];
	if (!path)
		return (NULL);
	return (path);
}

static void	update_env_pwd(char ***envp, char *old_pwd, char **cmd)
{
	char	*pwd_buffer;

	pwd_buffer = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	modify_env(envp, pwd_buffer);
	free(pwd_buffer);
	old_pwd = getcwd(NULL, 0);
	if (cmd[1] && cmd[1][0] == '-' && !cmd[1][1])
		ft_putendl_fd(old_pwd, 1);
	pwd_buffer = ft_strjoin("PWD=", old_pwd);
	modify_env(envp, pwd_buffer);
	free(pwd_buffer);
	free(old_pwd);
}

int	handle_cd(char **cmd, char ***envp)
{
	char	*path;
	char	*old_pwd;

	path = find_path(cmd, envp);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	update_env_pwd(envp, old_pwd, cmd);
	return (0);
}
