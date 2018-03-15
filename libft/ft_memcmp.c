/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:05:41 by coralie           #+#    #+#             */
/*   Updated: 2017/03/23 05:14:48 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p;
	const unsigned char	*p2;

	i = 0;
	p = (const unsigned char*)s1;
	p2 = (const unsigned char*)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (*(p + i) != *(p2 + i))
			return ((int)p[i] - p2[i]);
		i++;
	}
	return (0);
}
