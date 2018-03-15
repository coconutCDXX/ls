/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:37:38 by cwartell          #+#    #+#             */
/*   Updated: 2017/12/28 00:40:08 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_reverse(t_list **begin_list)
{
	t_list	*list;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = NULL;
	list = *begin_list;
	if (!list || !(list->next))
		return ;
	tmp = list->next;
	tmp2 = tmp->next;
	list->next = NULL;
	tmp->next = list;
	while (tmp2)
	{
		list = tmp;
		tmp = tmp2;
		tmp2 = tmp2->next;
		tmp->next = list;
	}
	*begin_list = tmp;
}
