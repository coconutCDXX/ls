/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 13:00:20 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 09:35:35 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *str, char c)
{
	int	ret;
	int	i;
	int	check;

	i = 0;
	ret = 0;
	check = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			i++;
			check = 1;
		}
		if (check == 1)
		{
			ret++;
			check = 0;
		}
	}
	return (ret);
}

static int	sizeof_word(char const *str, int i, char c)
{
	int	ret;

	ret = 0;
	while (str[i] != c && str[i] != '\0')
	{
		ret++;
		i++;
	}
	return (ret);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		word;
	int		w_count;
	char	**p;

	if (!s)
		return (NULL);
	i = 0;
	word = 0;
	w_count = word_count(s, c);
	if (!(p = (char**)malloc(sizeof(char *) * w_count + 1)))
		return (NULL);
	while (word < w_count)
	{
		while (s[i] == c)
			i++;
		p[word] = ft_strsub(s, i, (sizeof_word(s, i, c)));
		if (!(p[word]))
			return (NULL);
		i = i + sizeof_word(s, i, c);
		word++;
	}
	p[word] = NULL;
	return (p);
}
