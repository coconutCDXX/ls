/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:14:21 by coralie           #+#    #+#             */
/*   Updated: 2017/03/24 07:58:44 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	if (!s || !f)
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (*(s + ++i))
		ret[i] = f(i, s[i]);
	return (ret);
}
