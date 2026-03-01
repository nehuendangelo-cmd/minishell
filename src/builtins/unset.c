/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:09:27 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/01 00:01:38 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset(char ***envp, char *cmd)
{
		int		i;
	char **new_envp;
	int			to_delete;
	int			j;

	j = 0;
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
      return ;   
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return ;
	i = 0;
	
	while ((*envp)[i])
  {
      if (i != to_delete)
          new_envp[j++] = (*envp)[i];
      i++;
  }
	new_envp[j] = NULL;
	free(*envp);
	*envp = new_envp;
}
