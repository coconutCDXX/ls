/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:35 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 02:13:26 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	sort_command(t_info *sinfo, t_opt opt)
{
	sort_by_alpha(&sinfo);
	if (opt.t == TRUE)
		sort_by_time(&sinfo, opt);
	if (opt.r == TRUE)
		sort_by_r(&sinfo, opt);
	print_rec(&sinfo, opt);
	delete_me(sinfo);
}

void	sort_by_r(t_info **sinfo, t_opt opt)
{
	t_info *newstart;
	t_info *current;
	t_info *saved_new;

	current = *sinfo;
	newstart = *sinfo;
	while (current->next != NULL)
	{
		while (current->next->next)
			current = current->next;
		if (newstart == *sinfo)
		{
			saved_new = current->next;
			newstart = current->next;
			newstart->next = saved_new;
			current->next = NULL;
		}
		else
		{
			saved_new->next = current->next;
			current->next = NULL;
			saved_new = saved_new->next;
		}
		if (opt.R == TRUE && current->tree != NULL)
			sort_by_r(&(current->tree), opt);
		current = *sinfo;
	}
	saved_new->next = current;
	saved_new->next->next = NULL;
	*sinfo = newstart;
}

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
		if (current->tree != NULL)
			sort_by_alpha(&(current->tree));
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
