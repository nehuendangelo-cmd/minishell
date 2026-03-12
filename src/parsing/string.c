/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khderdou <khderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 19:46:14 by khderdou          #+#    #+#             */
/*   Updated: 2026/03/12 19:46:16 by khderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_shell_substr(const char *s, int start, int len)
{
	if (!s || len <= 0)
		return (NULL);
	return (ft_substr(s, start, len));
}

char	*ft_strjoin_shell(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (ft_strjoin(s1, s2));
}

int	ft_string_vide(const char *s)
{
	if (!s || ft_strlen(s) == 0)
		return (1);
	return (0);
}

int	ft_strcmp_shell(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (1);
	return (0);
}
