/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:46:54 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 23:20:28 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *str, int *i, char **envp, int last_status)
{
	char	*tmp;
	char	*var;
	int		start;

	(*i)++;
	if (str[*i] == '?')
		return (tmp = ft_itoa(last_status), (*i)++, tmp);
	if (str[*i] == '$')
		return (tmp = ft_itoa(getpid()), (*i)++, tmp);
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	tmp = ft_get_env_value(envp, var);
	free(var);
	if (tmp)
		return (ft_strdup(tmp));
	else
		return (ft_strdup(""));
}

// gere l'entree/sortie d'une zone de guillemets (simple ou double)
// retourne 1 si le caractere courant etait un guillemet, 0 sinon
int	ft_gere_guillemet(char c, char *quote, int *i)
{
	if (c != '\'' && c != '"')
		return (0);
	if (!*quote)
	{
		*quote = c;
		(*i)++;
		return (1);
	}
	if (*quote == c)
	{
		*quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

// parcourt le mot et expande les $variables en respectant les guillemets
char	*ft_expand_word(char *str, char **envp, int last_status)
{
	int		i;
	char	*res;
	char	*val;
	char	quote;

	i = 0;
	quote = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (ft_gere_guillemet(str[i], &quote, &i))
			continue ;
		if (str[i] == '$' && quote != '\'')
		{
			val = expand_variable(str, &i, envp, last_status);
			res = ft_strjoin_free(res, val);
			free(val);
		}
		else
			res = ft_charjoin(res, str[i++]);
	}
	return (res);
}

char	*ft_get_env_value(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] && ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
			return (&envp[i][ft_strlen(name) + 1]);
		i++;
	}
	return (NULL);
}

int	is_redirection_prev(t_token *token)
{
	if (!token || !token->prev)
		return (0);
	if (token->prev->type == TOK_REDIR_IN || token->prev->type == TOK_REDIR_OUT
		|| token->prev->type == TOK_APPEND || token->prev->type == TOK_HEREDOC)
		return (1);
	return (0);
}
