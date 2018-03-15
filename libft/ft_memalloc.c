/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:06:42 by coralie           #+#    #+#             */
/*   Updated: 2017/03/15 02:07:14 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*p;
	size_t	i;

	p = (void *)malloc(sizeof(*p) * size + 1);
	if (size > 4294967295)
		return (NULL);
	i = -1;
	if (p == NULL)
		return (NULL);
	ft_bzero(p, size);
	return (p);
}
