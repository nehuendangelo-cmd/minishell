/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:45:56 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 19:45:59 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_expanse(char *str, int i, int *exp)
{
	char	quote;
	int		pos;

	if (!str || !str[i])
		return (i);
	quote = str[i];
	pos = i + 1;
	if (quote == '"')
		*exp = 1;
	else
		*exp = 0;
	while (str[pos] && str[pos] != quote)
		pos++;
	if (!str[pos])
		return (-1);
	return (pos + 1);
}

int	ft_check_quote(char *str, int *err)
{
	int	i;
	int	exp;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = ft_quote_expanse(str, i, &exp);
			if (i == -1)
				return (0);
			if (err)
				*err = exp;
		}
		else
			i++;
	}
	return (1);
}
