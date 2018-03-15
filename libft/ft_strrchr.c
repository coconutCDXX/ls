/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:37:52 by coralie           #+#    #+#             */
/*   Updated: 2017/03/23 07:05:08 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = ft_strlen(s);
	p = (char *)s;
	if (c == '\0')
		return (p + i);
	while (i > 0)
	{
		if (*(s + i) == (char)c)
			return (p + i);
		i--;
	}
	if (s[0] == (char)c)
		return (p);
	return (NULL);
}
