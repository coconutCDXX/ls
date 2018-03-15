/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:35:48 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 07:53:12 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	int		c;

	if (!s)
		return (NULL);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = -1;
	c = (int)len;
	if (c == 0)
	{
		*(new) = '\0';
		return (new);
	}
	while (++i < len)
		*(new + i) = *(s + start++);
	return (new);
}
