/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:08:20 by coralie           #+#    #+#             */
/*   Updated: 2017/03/15 02:54:38 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*(s1 + i) == *(s2 + i))
	{
		i++;
		if (*(s1 + i) == *(s2 + i) && *(s1 + i) == '\0')
			return (1);
	}
	return (0);
}
