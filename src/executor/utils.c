/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:35:36 by nd-angel          #+#    #+#             */
/*   Updated: 2026/03/12 18:36:41 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_count(t_cmd *cmd)
{
	t_cmd	*count;
	int		i;

	i = 0;
	count = cmd;
	while (count)
	{
		count = count->next;
		i++;
	}
	return (i);
}