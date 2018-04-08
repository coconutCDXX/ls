/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:35 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/08 05:28:25 by cwartell         ###   ########.fr       */
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
		sort_recursive(&sinfo, opt);
	print_rec(&sinfo, opt, b);
	delete_me(sinfo);
}

int		read_and_stat(t_info *sinfo, char *treename)
{
	struct stat	stats;

	if (stat(treename, &stats) == -1 && lstat(treename, &stats) != 0)
	{
		sinfo->read_and_stat = 0;
		sinfo->p_dir_cont = 1;
	}
	else
		sinfo->read_and_stat = 1;
	return (sinfo->read_and_stat);
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

void	sort_recursive(t_info **sinfo, t_opt opt)
{
	t_info *current;

	current = *sinfo;
	while (current->next)
	{
		if (current->p_dir_cont == 0)
		{
			current = current->next;
			continue;
		}
		if (current->tree != NULL)
		{
			sort_by_alpha(&(current->tree));
			if (opt.t == TRUE)
				sort_by_time(&(current->tree));
			if (opt.r == TRUE)
				sort_by_r(&(current->tree));
			printf("sub[%s][%s]\n", current->filename, current->tree->filename);

			if (current->tree->tree != NULL)
			{
				printf("inside[%s]\n", current->tree->tree->filename);
				sort_recursive(&current->tree->tree, opt);
			}
		}
		current = current->next;
	}
	printf("i sorted recursvilely\n\n\n");
}


