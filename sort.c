#include "ls_lib.h"

void		sort_command(t_info *sinfo, t_opt opt)
{
	printf("enterring command control sort over over\n");
	sort_by_alpha(&sinfo);
	printf("i sorted by alpha!!!!!!!\n");
	if (opt.t == TRUE)
	{
		sort_by_time_xor_rev(&sinfo, opt);
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
void		sort_by_time_xor_rev(t_info **sinfo, t_opt opt)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		printf("where are we [%s] [%lld]\n", current->filename, (long long)current->time_sort);
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
				printf("new start![%s]\n", current->filename);
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
		// else if (current->time_sort > current->next->time_sort && opt.r == TRUE)
		// {
		// 	printf("this is happening?\n");
		// 	tmp = current->next;
		// 	current->next->next = current;
		// 	current = tmp;
		// 	free(tmp);
		// 	current = *sinfo;
		// 	continue;
		// }
		// if (opt.R == TRUE && current->tree != NULL)
		// 	sort_by_time_xor_rev(&(current->tree), opt);
	}
	//*sinfo = start;
	printf("whats the new start [%s]\n", start->filename);
}

void			sort_folders(char **ret, t_opt opt)
{
	int	x;
	char	*tmp;

	x = 0;
	while (ret[x + 1] != NULL)
	{
		if (check_alpha(ret[x], ret[x + 1]))
		{
			tmp = ret[x + 1];
			ret[x + 1] = ret[x];
			ret[x] = tmp;
			x = 0;
			continue;
		}
		x++;
	}
}
