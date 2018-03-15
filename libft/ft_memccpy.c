/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:48:15 by coralie           #+#    #+#             */
/*   Updated: 2017/03/15 04:09:59 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*pd;
	char	*ps;

	i = -1;
	pd = (char *)dest;
	ps = (char *)src;
	while (++i < n)
	{
		*(pd + i) = (unsigned char)*(ps + i);
		if ((unsigned char)*(ps + i) == (unsigned char)c)
			return (pd + i + 1);
	}
	return (NULL);
}
