/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:46:54 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/13 00:00:00 by khderdou         ###   ########.fr       */
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

static char	*expand_tilde(char **envp, int *i)
{
	char	*val;

	val = ft_get_env_value(envp, "HOME");
	if (val)
		val = ft_strdup(val);
	else
		val = ft_strdup("~");
	(*i)++;
	return (val);
}

static char	*expand_backslash(char *str, int *i)
{
	char	tmp[2];

	(*i)++;
	if (!str[*i])
		return (ft_strdup(""));
	tmp[0] = str[*i];
	tmp[1] = '\0';
	(*i)++;
	return (ft_strdup(tmp));
}

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
			val = expand_variable(str, &i, envp, last_status);
		else if (!quote && str[i] == '~' && !i
			&& (!str[1] || str[1] == '/' || str[1] == ' '))
			val = expand_tilde(envp, &i);
		else if (str[i] == '\\' && !quote)
			val = expand_backslash(str, &i);
		else
			val = ft_charjoin(ft_strdup(""), str[i++]);
		res = ft_strjoin_free(res, val);
		free(val);
	}
	return (res);
}
