#include "ls_lib.h"

void		sort_command(t_info *sinfo, t_opt opt)
{
	printf("enterring command control sort over over\n");
	sort_by_alpha(&sinfo);
	printf("i sorted by alpha!!!!!!!\n");
	if (opt.t == TRUE)
	{
		sort_by_time(&sinfo, opt);
		printf("i sorted by t\n");
	}
	if (opt.r == TRUE)
		sort_by_r(&sinfo, opt);
	printf("sort_command is sinfo alive? [%s]\n", sinfo->filename);
	print_rec(&sinfo, opt);
	// if R print all else just print
	// if a or l print addition info
}

void		sort_by_r(t_info **sinfo, t_opt opt)
{
	t_info *newstart;
	t_info *current;
	t_info *saved_new;

	current = *sinfo;
	newstart = *sinfo;
	while (current->next != NULL)
	{
		while (current->next->next)
		{
			printf("next next [%p] next [%s][%p]\n",current->next->next, current->next->filename, current->next);
			current = current->next;
		}
		printf("current is [%s]\n", current->filename);
		if (newstart == *sinfo)
		{
			saved_new = current->next;
			newstart = current->next;
			newstart->next = saved_new;
			//free(current->next);
			current->next = NULL;
			printf("new start [%s] [%p]\n", saved_new->filename, current->next);
		}
		else
		{
			saved_new->next = current->next;
			//free(current->next);
			current->next = NULL;

			saved_new = saved_new->next;
			printf("saved_new->next [%s]\n", saved_new->filename);
		}
		if (opt.R == TRUE && current->tree != NULL)
			sort_by_r(&(current->tree), opt);
		current = *sinfo;
	}
	saved_new->next = current;
	//free(current);
	saved_new->next->next = NULL;
	*sinfo = newstart;
}
void			sort_by_alpha(t_info **sinfo)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		printf("stats of cur [%s]\n", current->filename);
		if (check_alpha(current->filename, current->next->filename))
		{
			tmp = current->next;
			current->next = tmp->next;
			tmp->next = current;
			if (*sinfo == current)
			{
				*sinfo = tmp;
				current = *sinfo;
			}
			else
			{
				start->next = tmp;
				current = *sinfo;
			}
		}
		else
		{
			start = current;
			current = current->next;
			printf("new start[%s]\n", current->filename);
		}
		// if (current->tree != NULL)
		// {
		// 	printf("tree mode fuck up\n");
		// 	sort_by_alpha(&(current->tree));
		// }
	}
}

int		check_alpha(char *a, char *b)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if(!(strcmp(b, "..")) && !(strcmp(a, ".")))
		return 0;
	if (a[j] == '.')
		j++;
	if (b[i] == '.')
		i++;
	if (a[j] >= 65 && a[j] <= 90 && !(b[i] >= 65 && b[i] <= 90))
	{	if (a[j] + 32 > b[i])
			return (1);
		else
			return (0);
		}
	if (b[i] >= 65 && b[i] <= 90 && !(a[j] >= 65 && a[j] <= 90))
		{if (b[i] + 32 < a[j])
			return (1);
		else
			return (0);
		}
	if (a[j] > b[i])
		return (1);
	if (a[j] == b[i])
		return (check_alpha(a + 1, b + 1));
	return (0);
}
void		sort_by_time(t_info **sinfo, t_opt opt)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		//printf("where are we [%s] [%lld]\n", current->filename, (long long)current->time_sort);
		//printf("next one [%s] [%lld]\n\n", current->next->filename, (long long)current->next->time_sort);
		if (current->time_sort < current->next->time_sort)
		{
			tmp = current->next;
			current->next = tmp->next;
			tmp->next = current;
			if (*sinfo == current)
			{
				*sinfo = tmp;
				current = *sinfo;
				//printf("new start![%s]\n", current->filename);
			}
			else
			{
				start->next = tmp;
				current = *sinfo;
				printf("in the sort part a [%s] [%lld]\n", start->filename, (long long)current->time_sort);
				printf("in the sort part b [%s] [%lld]\n\n", start->next->filename, (long long)current->next->time_sort);
			}
		}
		else
		{
			start = current;
			current = current->next;
			printf("aliv?\n");
		}
	}
	printf("whats the new start [%s]\n", start->filename);
}

void			sort_folders(char **f, t_opt opt)
{
	int	x;
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

char			**sort_rev_folders(char **f)
{
	int	y;
	int	x;
	int	z;
	char	**new;

	y = 0;
	x = 0;
	while (f[y])
		y++;
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

time_t		check_time(char *t)
{
	struct stat	stats;

	stat(t, &stats);
	return (stats.st_mtime);
}

void			sort_time_folders(char **f)
{
	int x;
	char *tmp;

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
