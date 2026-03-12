/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:46:36 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 19:59:36 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_tokens(t_token *tokens, char **envp, int last_status)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == WORD && tokens->quote_type != SINGLE_QUOTE)
		{
			if (ft_strchr(tokens->value, '$'))
			{
				expanded = ft_expand_word(tokens->value, envp, last_status);
				free(tokens->value);
				tokens->value = expanded;
			}
		}
		tokens = tokens->next;
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
