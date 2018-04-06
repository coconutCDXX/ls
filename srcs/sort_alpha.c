/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 01:47:25 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/06 03:53:20 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	sort_by_alpha(t_info **sinfo)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		if (check_alpha(current->filename, current->next->filename))
		{
			tmp = current->next;
			current->next = tmp->next;
			tmp->next = current;
			if (*sinfo == current)
				*sinfo = tmp;
			else
				start->next = tmp;
			current = *sinfo;
		}
		else
		{
			start = current;
			current = current->next;
		}
	}
}

int		check_alpha(char *a, char *b)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(ft_strcmp(a, ".")) || (!(ft_strcmp(a, ".."))
	&& ft_strcmp(b, ".") != 0))
		return (0);
	if (!(ft_strcmp(b, ".")) || (!(ft_strcmp(b, ".."))
	&& ft_strcmp(a, ".") != 0))
		return (1);
	while (a[j] == b[i])
	{
		j++;
		i++;
	}
	return (check_alpha_bis(b[i], a[j]));
}

int		check_alpha_bis(char x, char y)
{
	if (y >= 65 && y <= 90 && !(x >= 65 && x <= 90))
	{
		if (y > x)
			return (1);
		else
			return (0);
	}
	if (x >= 65 && x <= 90 && !(y >= 65 && y <= 90))
	{
		if (x < y)
			return (1);
		else
			return (0);
	}
	if (y > x)
		return (1);
	return (0);
}
