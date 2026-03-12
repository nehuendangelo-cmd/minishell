/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:45:40 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 19:45:43 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	ft_add_token_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*ft_create_quote_token(char *line, int start, int len, char quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->type = WORD;
	if (quote == '\'')
		token->quote_type = SINGLE_QUOTE;
	else
		token->quote_type = DUBBLE_QUOTE;
	token->value = ft_substr(line, start, len);
	return (token);
}

void	ft_add_word_quote_token(t_token **head, char *line, int *i)
{
	int		start;
	int		len;
	char	quote;
	t_token	*token;

	quote = line[*i];
	(*i)++;
	start = *i;
	len = 0;
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (line[*i] == quote)
		(*i)++;
	token = ft_create_quote_token(line, start, len, quote);
	if (!token)
		return ;
	ft_add_token_back(head, token);
}
