/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:08:33 by nd-angel          #+#    #+#             */
/*   Updated: 2025/11/12 21:23:25 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	len = 0;
	while (s[len] != c && s[len])
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

void	free_array(char	**array, int filled)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while (i < filled)
	{
		free(array[i]);
		i++;
	}
	free (array);
}

int	array_filler(char **array, char const *s, char c)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			array[y] = get_word(s + i, c);
			if (!array[y])
			{
				free_array(array, y);
				return (0);
			}
			y++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	array[y] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (array == NULL)
		return (NULL);
	if (!array_filler(array, s, c))
		return (NULL);
	return (array);
}
