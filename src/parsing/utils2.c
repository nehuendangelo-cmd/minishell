/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:47:02 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 23:20:28 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*ft_charjoin(char *s, char c)
{
	char	*res;
	int		len;

	len = ft_strlen(s);
	res = malloc(len + 2);
	ft_strcpy(res, s);
	res[len] = c;
	res[len + 1] = '\0';
	free(s);
	return (res);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_cmd	*error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (NULL);
}

int	is_redirection(int type)
{
	if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT || type == TOK_APPEND
		|| type == TOK_HEREDOC)
		return (1);
	return (0);
}
