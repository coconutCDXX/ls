/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:17:35 by coralie           #+#    #+#             */
/*   Updated: 2017/03/15 04:39:31 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*pd;
	char	*ps;

	i = -1;
	pd = (char *)dest;
	ps = (char *)src;
	if (dest > src)
		while (n-- > 0)
			*(pd + n) = *(ps + n);
	else
		while (++i < n)
			*(pd + i) = *(ps + i);
	return ((void*)pd);
}
