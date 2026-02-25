/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 19:18:41 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/14 20:03:10 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*last;
	t_list	*stock;

	if (lst == NULL || f == NULL)
	{
		newlist = NULL;
		return (newlist);
	}
	newlist = NULL;
	last = 0;
	while (lst)
	{
		stock = f(lst->content);
		last = ft_lstnew(stock);
		if (!last)
		{
			del(stock);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, last);
		lst = lst->next;
	}
	return (newlist);
}
