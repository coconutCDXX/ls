/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:30:47 by coralie           #+#    #+#             */
/*   Updated: 2017/03/23 04:34:34 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		makeitshorter(long a)
{
	int		i;
	long	d;

	i = 0;
	d = a;
	if (a < 0)
		i++;
	while (d != 0)
	{
		d = d / 10;
		i++;
	}
	return (a == 0 ? 1 : i);
}

char			*ft_itoa(int n)
{
	char	*new;
	int		j;
	long	k;

	j = 0;
	k = (long)n;
	if (!(new = (char*)malloc(sizeof(*new) * (makeitshorter(k) + 1))))
		return (NULL);
	j = makeitshorter(n);
	if (n < 0)
	{
		new[0] = '-';
		k = -k;
	}
	new[j] = '\0';
	new[--j] = k % 10 + '0';
	while (k /= 10)
		new[--j] = k % 10 + '0';
	return (new);
}
