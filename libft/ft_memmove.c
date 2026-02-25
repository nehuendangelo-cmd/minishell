/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:14:44 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/14 20:37:14 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*charsrc;
	unsigned char	*chardest;
	size_t			i;

	if (!dest && !src)
		return (0);
	charsrc = (unsigned char *) src;
	chardest = (unsigned char *) dest;
	if (chardest > charsrc && chardest < charsrc + n)
	{
		i = n;
		while (i--)
		{
			chardest[i] = charsrc[i];
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			chardest[i] = charsrc[i];
	}
	return (dest);
}
