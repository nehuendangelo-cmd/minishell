/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:27:50 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/08 22:41:23 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t siz)
{
	size_t	i;
	size_t	y;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	while (dest[dest_len] && dest_len < siz)
		dest_len++;
	src_len = ft_strlen(src);
	if (dest_len == siz)
		return (siz + src_len);
	i = dest_len;
	y = 0;
	while (src[y] && i + 1 < siz)
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	if (i < siz)
		dest[i] = '\0';
	return (dest_len + src_len);
}
