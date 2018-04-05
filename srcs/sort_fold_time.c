/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fold_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:11:07 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 02:13:38 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	sort_time_folders(char **f)
{
	int		x;
	char	*tmp;

	x = 0;
	while (f[x + 1] != NULL)
	{
		if (check_time(f[x]) < check_time(f[x + 1]))
		{
			tmp = f[x + 1];
			f[x + 1] = f[x];
			f[x] = tmp;
			x = 0;
			continue;
		}
		x++;
	}
}

void	sort_rev_folders(char **f)
{
	int		y;
	int		z;
	char	*save;

	z = 0;
	y = 0;
	while (f[z])
		z++;
	z--;
	while (y < z - y)
	{
		save = f[y];
		f[y] = f[z - y];
		f[z - y] = save;
		y++;
	}
}

void	sort_folders(char **f, t_opt opt)
{
	int		x;
	char	*tmp;

	x = 0;
	while (f[x + 1] != NULL)
	{
		if (check_alpha(f[x], f[x + 1]))
		{
			tmp = f[x + 1];
			f[x + 1] = f[x];
			f[x] = tmp;
			x = 0;
			continue;
		}
		x++;
	}
	if (opt.t)
		sort_time_folders(f);
	if (opt.r)
		sort_rev_folders(f);
}

void	sort_by_time(t_info **sinfo, t_opt opt)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		if (current->time_sort < current->next->time_sort)
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
		if (opt.R == TRUE && current->tree != NULL)
			sort_by_r(&(current->tree), opt);
	}
}

time_t	check_time(char *t)
{
	struct stat	stats;

	stat(t, &stats);
	return (stats.st_mtime);
}
