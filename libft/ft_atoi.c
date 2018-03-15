/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:10:14 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 06:21:09 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	size_t	a;
	int		neg;
	int		ret;

	a = 0;
	neg = 1;
	ret = 0;
	while (*(nptr + a) == '\n' || *(nptr + a) == '\t' ||
		*(nptr + a) == '\r' || *(nptr + a) == '\v' ||
		*(nptr + a) == '\f' || *(nptr + a) == ' ')
		a++;
	if (*(nptr + a) == '-')
		neg = -1;
	if (*(nptr + a) == '-' || *(nptr + a) == '+')
		a++;
	while (*(nptr + a) != '\0' && *(nptr + a) >= '0' && *(nptr + a) <= '9')
	{
		ret = (ret * 10) + (nptr[a++] - '0');
	}
	return (ret * neg);
}
