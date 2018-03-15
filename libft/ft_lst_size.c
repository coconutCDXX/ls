/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:31:59 by cwartell          #+#    #+#             */
/*   Updated: 2017/12/28 00:39:50 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lst_size(t_list *begin_list)
{
	int	i;

	i = 0;
	while (begin_list)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}
