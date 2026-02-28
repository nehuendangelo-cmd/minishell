/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:06:08 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/08 20:45:27 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			length;
	long int	nb;

	nb = n;
	length = count(nb);
	result = malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	result[length--] = '\0';
	if (nb == 0)
		result[length] = '0';
	while (nb > 0)
	{
		result[length] = (nb % 10) + 48;
		nb /= 10;
		length--;
	}
	return (result);
}
