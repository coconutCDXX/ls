/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:08:29 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 03:50:41 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	i = -1;
	while (*(s + ++i))
		ret[i] = f(s[i]);
	return (ret);
}
