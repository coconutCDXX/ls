/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:00:59 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 10:29:49 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	k = 0;
	l = i;
	if (i + j == 0)
		return (0);
	if (size < i)
		return (j + size);
	while (i < size - 1 && *(src + k) != '\0')
	{
		*(dst + i) = *(src + k);
		i++;
		k++;
	}
	dst[i] = '\0';
	if (j == i)
		return (j <= size ? j : size);
	if (size > l + j)
		return (i);
	return (j + l);
}
