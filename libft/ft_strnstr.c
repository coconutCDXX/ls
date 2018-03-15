/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:05:30 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 07:28:00 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needl, size_t len)
{
	int		i;
	int		h;
	size_t	j;
	char	*p;

	h = 0;
	j = 0;
	p = (char *)hay;
	if (ft_strlen(needl) == 0 || hay == needl)
		return (p);
	while (hay[h] != '\0' && len-- > 0)
	{
		i = h;
		while (*(hay + i) == *(needl + j) && hay[i] != '\0'
			&& j <= len)
		{
			j++;
			if (*(needl + j) == '\0')
				return (p + (i - j) + 1);
			i++;
		}
		h++;
		j = 0;
	}
	return (NULL);
}
