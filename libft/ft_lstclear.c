/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:54:51 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/10 13:17:06 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*stock;
	t_list	*temp;

	stock = *lst;
	while (stock)
	{
		del(stock->content);
		temp = stock->next;
		free(stock);
		stock = temp;
	}
	*lst = NULL;
}
