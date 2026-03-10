/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:11:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/10 18:47:22 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    is_numeric(char *str)                      
  {                                                        
      int       i;                                         
                                                           
      i = 0;
			if (!str)
				return (0);
      if (str[i] == '+' || str[i] == '-')
          i++;
      if (!str[i])
          return (0);
      while (str[i])
      {
          if (!ft_isdigit(str[i]))
              return (0);
          i++;
      }
      return (1);
  }
	
void handle_exit(char **cmd, int last_exit_code)
{
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": too many arguments", 2);
			return ;
		}
		if (is_numeric(cmd[1]))
			exit(ft_atoi(cmd[1]));
		else 
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
	}
	else
		exit(last_exit_code);
}