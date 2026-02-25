/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:42 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/08 22:20:06 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		y;

	y = 0;
	i = 0;
	if (little[y] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		y = 0;
		if (big[i] == little[y])
		{
			while (big[i + y] == little[y] && big[i + y]
				&& little[y] && i + y < len)
				y++;
			if (!little[y])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
