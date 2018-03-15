/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coralie <coralie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:40:49 by coralie           #+#    #+#             */
/*   Updated: 2017/03/11 00:55:38 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	i;
	int		j;

	i = ft_strlen(s);
	new = (char *)malloc(sizeof(*new) * i + 1);
	if (new == NULL)
		return (NULL);
	j = -1;
	while (s[++j] != '\0')
	{
		new[j] = s[j];
	}
	new[j] = '\0';
	return (new);
}
