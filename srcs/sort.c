/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:35 by cwartell          #+#    #+#             */
/*   Updated: 2018/03/14 19:28:39 by coralie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	sort_command(t_info *sinfo, t_opt opt)
{
	//printf("enterring command control sort over over\n");
	sort_by_alpha(&sinfo);
//	printf("i sorted by alpha!!!!!!!\n");
	if (opt.t == TRUE)
	{
		sort_by_time(&sinfo, opt);
		//printf("i sorted by t\n");
	}
	if (opt.r == TRUE)
		sort_by_r(&sinfo, opt);
//	printf("sort_command is sinfo alive? [%s]\n", sinfo->filename);
	print_rec(&sinfo, opt);
//	printf("print all done return\n");
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
		//printf("secondary check [%s] [%s]\n", current->filename, current->next->filename);
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
		{
			//printf("dangerzone\n");
			sort_by_alpha(&(current->tree));
		}
		//printf("third\n");
	}
}

// void	sort_trees(t_info **sinfo)
// {
// 	t_info *current;
// 	t_info *start;
//
// 	current = *sinfo;
// 	start = *sinfo;
// 	while (current->next)
// 	{
// 		if (current->tree != NULL)
// 		{
// 			current = current->tree;
// 			while (current->next)
// 			{
// 				sort_by_alpha(&current);
// 				current = current->next;
// 			}
// 		}
// 		else
// 			start = start->next;
// 	}
// }

int		check_alpha(char *a, char *b)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(strcmp(b, "..")) && !(strcmp(a, ".")))
		return (0);
	if (a[j] == '.')
		j++;
	if (b[i] == '.')
		i++;
	if (a[j] >= 65 && a[j] <= 90 && !(b[i] >= 65 && b[i] <= 90))
	{
		if (a[j] + 32 > b[i])
			return (1);
		else
			return (0);
	}
	if (check_alpha_bis(b[i], a[j]) != 2)
		return (check_alpha_bis(b[i], a[j]));
	if (a[j] == b[i])
		return (check_alpha(a + 1, b + 1));
	return (0);
}

int		check_alpha_bis(char x, char y)
{
	if (x >= 65 && x <= 90 && !(y >= 65 && y <= 90))
	{
		if (x + 32 < y)
			return (1);
		else
			return (0);
	}
	if (y > x)
		return (1);
	return (2);
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
		f = sort_rev_folders(f);
}

char	**sort_rev_folders(char **f)
{
	int		y;
	int		x;
	int		z;
	char	**new;

	y = 0;
	x = 0;
	while (f[y])
		y++;
	y--;
	new = (char**)malloc(sizeof(char*) * y);
	while (y - x >= 0)
	{
		z = strlen(f[y - x]);
		new[x] = (char*)malloc(sizeof(char) * z + 1);
		strcpy(new[x], f[y - x]);
		x++;
	}
	return (new);
}

time_t	check_time(char *t)
{
	struct stat	stats;

	stat(t, &stats);
	return (stats.st_mtime);
}

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
