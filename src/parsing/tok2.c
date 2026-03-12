/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:46:36 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 23:14:33 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_quote_char(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	expand_word_token(t_token *cur, char **envp, int last_status,
		int *quoted)
{
	char	*expanded;

	*quoted = has_quote_char(cur->value);
	expanded = ft_expand_word(cur->value, envp, last_status);
	free(cur->value);
	cur->value = expanded;
}

static t_token	*remove_token(t_token **tokens, t_token *prev, t_token *cur)
{
	t_token	*next;

	next = cur->next;
	if (prev)
		prev->next = next;
	else
		*tokens = next;
	free(cur->value);
	free(cur);
	return (next);
}

void	ft_expand_tokens(t_token **tokens, char **envp, int last_status)
{
	t_token	*cur;
	t_token	*prev;
	int		quoted;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		if (cur->type == WORD)
		{
			expand_word_token(cur, envp, last_status, &quoted);
			if (!quoted && cur->value[0] == '\0')
			{
				cur = remove_token(tokens, prev, cur);
				continue ;
			}
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_add_op_token(t_token **head, char *line, int *i)
{
	if (line[*i] && line[*i + 1] && ((line[*i] == '<' && line[*i + 1] == '<')
			|| (line[*i] == '>' && line[*i + 1] == '>')))
		ft_add_double_op_token(head, line, i);
	else
		ft_add_single_op_token(head, line, i);
}
