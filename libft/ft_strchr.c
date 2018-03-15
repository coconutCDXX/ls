/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:30:02 by coralie           #+#    #+#             */
/*   Updated: 2017/03/13 18:54:37 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char)c)
			return (p + i);
		i++;
	}
	if (c == '\0')
		return (p + i);
	return (NULL);
}
