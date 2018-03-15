/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:52:03 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 07:58:06 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	st;
	size_t	end;
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	st = ft_strlen(s1);
	end = ft_strlen(s2);
	i = -1;
	j = -1;
	if (!(p = (char*)malloc(sizeof(*p) * (st + end + 1))))
		return (NULL);
	while (*(s1 + ++i))
		*(p + i) = *(s1 + i);
	while (*(s2 + ++j))
		*(p + i++) = *(s2 + j);
	*(p + i) = '\0';
	return (p);
}
