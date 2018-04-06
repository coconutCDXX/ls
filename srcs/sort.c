/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:35 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/06 10:31:21 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	sort_command(t_info *sinfo, t_opt opt, t_boolean b)
{
	sort_by_alpha(&sinfo);
	if (opt.t == TRUE)
		sort_by_time(&sinfo);
	if (opt.r == TRUE)
		sort_by_r(&sinfo);
	if (opt.cr == TRUE)
		sort_recursive(sinfo);
	print_rec(&sinfo, opt, b);
	if (opt.l == TRUE)
		check_permissions(sinfo);
	delete_me(sinfo);
}

void	check_permissions(t_info *sinfo)
{
	while (sinfo)
	{
		if (sinfo->p_dir_cont == 0)
		{
			write(1, sinfo->filename, ft_strlen(sinfo->filename));
			write(1, ":\n", 2);
			print_error_perm(sinfo->filename);
		}
		sinfo = sinfo->next;
	}
}

void	sort_by_r(t_info **sinfo)
{
	t_info *current;
	t_info *prev;
	t_info *next;

	current = *sinfo;
	prev = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*sinfo = prev;
}

void	sort_recursive(t_info *sinfo)
{
	t_info *current;

	current = sinfo;
	while (current->next)
	{
		if (current->p_dir_cont == 0)
		{
			current = current->next;
			continue;
		}
		if (current->tree != NULL)
			sort_by_alpha(&(current->tree));
		if (current->tree != NULL)
			sort_by_time(&(current->tree));
		if (current->tree != NULL)
			sort_by_r(&(current->tree));
		current = current->next;
	}
}
