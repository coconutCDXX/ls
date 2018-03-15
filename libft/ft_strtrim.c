/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:17:41 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 05:17:06 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	findspaces(char const *s, int a, size_t l)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (a == 1)
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		return (i);
	}
	else
		while ((s[l] == ' ' || s[l] == '\t' ||
		s[l] == '\n') && s[l - 1] != '\0')
		{
			k++;
			l--;
		}
	return (k);
}

char		*ft_strtrim(char const *s)
{
	size_t	l;
	size_t	i;
	size_t	k;
	char	*new;

	if (!s)
		return (NULL);
	l = ft_strlen(s) - 1;
	i = findspaces(s, 1, l);
	k = findspaces(s, 2, l);
	if (i == l + 1)
	{
		new = ft_strnew(1);
		return (new);
	}
	if (!(new = ft_strnew(l - i - k + 1)))
		return (NULL);
	l = l - k;
	k = 0;
	if (new == NULL)
		return (NULL);
	while (i <= l)
		new[k++] = s[i++];
	new[k] = '\0';
	return (new);
}
