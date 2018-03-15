/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:46:09 by coralie           #+#    #+#             */
/*   Updated: 2017/03/14 00:33:07 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	p = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (p);
	while (haystack[i] != '\0')
	{
		while (*(haystack + i) == *(needle + j))
		{
			j++;
			if (*(needle + j) == '\0')
				return (p + (i - j + 1));
			i++;
		}
		if (j > 0)
			i = i - j + 1;
		else
			i++;
		j = 0;
	}
	return (NULL);
}
