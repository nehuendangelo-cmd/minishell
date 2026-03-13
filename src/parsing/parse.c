/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:45:48 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 19:45:51 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_principal(char *line)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (ft_ispace(line[i]))
		{
			i++;
			continue ;
		}
		if (ft_is_op(line[i]))
			ft_add_op_token(&token, line, &i);
		else
			ft_add_word_token(&token, line, &i);
	}
	return (token);
}

int	parse_precheck(char *line)
{
	int	res;

	if (!ft_check_quote(line, NULL))
		return (error("syntax error: unclosed quote"), 1);
	res = ft_check_debut_fin(line);
	if (res == 0)
		return (error("syntax error near unexpected token `|'"), 1);
	if (res == -1)
		return (error("syntax error: unexpected end of file"), 1);
	if (!ft_check_pipe(line))
		return (error("syntax error near unexpected token `|'"), 1);
	if (!ft_check_redirection(line))
		return (error("syntax error near unexpected token `newline'"), 1);
	return (0);
}

int	parse_tokenize(char *line, t_token **tokens)
{
	*tokens = parse_principal(line);
	if (!*tokens && line && line[0])
	{
		error("tokenization failed");
		return (1);
	}
	return (0);
}

int	parse_build_cmds(t_token *tokens, t_cmd **cmd)
{
	*cmd = ft_build_command(tokens);
	if (!*cmd && tokens)
		return (1);
	return (0);
}

int	appel_parse(char *line, t_cmd **cmd, t_shell *shell)
{
	t_token	*tokens;

	if (!cmd)
		return (1);
	*cmd = NULL;
	if (!line || !line[0])
		return (0);
	if (parse_precheck(line))
		return (1);
	if (parse_tokenize(line, &tokens))
		return (1);
	if (shell)
		ft_expand_tokens(&tokens, shell->envp, shell->last_exit);
	if (parse_build_cmds(tokens, cmd))
		return (free_tokens(tokens), 1);
	free_tokens(tokens);
	return (0);
}
