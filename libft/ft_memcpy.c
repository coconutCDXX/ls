/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:45:35 by coralie           #+#    #+#             */
/*   Updated: 2017/03/09 03:13:57 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*p2;

	i = 0;
	p = (char*)dest;
	p2 = (char*)src;
	while (i++ < n)
		*p++ = *p2++;
	return (dest);
}
