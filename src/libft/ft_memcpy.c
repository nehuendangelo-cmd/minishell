/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:07:14 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/14 20:39:19 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*charsrc;
	unsigned char			*chardest;

	if (!dest && !src)
		return (NULL);
	chardest = (unsigned char *) dest;
	charsrc = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		chardest[i] = charsrc[i];
		i++;
	}
	return (dest);
}
