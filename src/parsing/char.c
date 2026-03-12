/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:45:21 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 21:49:00 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_quote(char *str, int i)
{
	char	quote;
	int		pos;

	if (!str || !str[i])
		return (i);
	quote = str[i];
	pos = i + 1;
	while (str[pos] && str[pos] != quote)
		pos++;
	if (str[pos] == quote)
		return (pos + 1);
	return (pos);
}

int	ft_op_valid(char *str, int i)
{
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_skip_quote(str, i);
		else if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		else
			i++;
	}
	return (1);
}

int	ft_syntaxe_op(char *str, int i)
{
	char	n;
	char	c;

	if (!str || !str[i])
		return (1);
	while (str && str[i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i = ft_skip_quote(str, i);
		c = str[i];
		if ((c == '|' || c == '&' || c == '<' || c == '>') && str[i + 1])
		{
			n = str[i + 1];
			if ((n == '|' || n == '&' || n == '<' || n == '>') && c != n)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_ispace(int s)
{
	return (s == ' ' || s == '\t' || s == '\n' || s == '\r' || s == '\v'
		|| s == '\f');
}

int	word_is_ok(char c)
{
	if (!c)
		return (0);
	else if (ft_ispace(c))
		return (0);
	else if (c == '\'' || c == '\"')
		return (0);
	else if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}
