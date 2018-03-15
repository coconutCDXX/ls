/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 17:51:36 by cwartell          #+#    #+#             */
/*   Updated: 2017/04/01 17:54:54 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void		*p;

	if (!ptr || !size)
		return (NULL);
	if (!(p = ft_strnew(size)))
		return (NULL);
	ft_strcpy(p, ptr);
	return (p);
}
