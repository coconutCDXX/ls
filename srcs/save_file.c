/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:26:53 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/12 04:37:29 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

int		spec_file(int ac, char **av, t_opt opt, t_info *sinfo)
{
	int			x;
	struct stat	stats;
	int			totalnf;
	int			nonf;

	x = 1;
	totalnf = files_count(av);
	nonf = totalnf;
	while (ac > 1)
	{
		valid_file(av, &x, &ac);
		if ((!(stat(av[x], &stats)) || !(lstat(av[x], &stats)))
		&& !(S_ISDIR(stats.st_mode)))
		{
			save_data2(sinfo, av[x], nonf, totalnf);
			nonf--;
		}
		if (ac == 2)
			end_specific_file(sinfo, opt, av);
		ac--;
		x++;
	}
	return (totalnf != 0 ? 1 : 0);
}

void	valid_file(char **av, int *x, int *ac)
{
	struct stat	stats;
	int			p;

	p = *ac;
	while (p > *x)
	{
		if ((!(stat(av[(*x)], &stats)) && S_ISDIR(stats.st_mode))
		|| (av[(*x)][0] == '-'))
		{
			*ac = *ac - 1;
			*x = *x + 1;
		}
		else
			return ;
	}
}

void	end_specific_file(t_info *sinfo, t_opt opt, char **av)
{
	print_errors(av);
	if (sinfo->filename != NULL)
		sort_command(sinfo, opt, FALSE);
}

int		files_count(char **av)
{
	int			x;
	int			nf;
	struct stat	stats;

	x = 1;
	nf = 0;
	while (av[x])
	{
		if ((!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode)))
		|| (!(lstat(av[x], &stats)) && !(S_ISDIR(stats.st_mode))))
			nf++;
		x++;
	}
	return (nf);
}

void	save_data2(t_info *sinfo, char *filename, int nf, int tf)
{
	struct stat stats;

	if (nf < tf)
	{
		while (nf < tf - 1)
		{
			sinfo = sinfo->next;
			tf--;
		}
		sinfo->next = (t_info*)malloc(sizeof(t_info));
		sinfo = sinfo->next;
	}
	if (save_data2_lstat(sinfo, filename, nf))
		return ;
	stat(filename, &stats);
	set_types_name(sinfo, filename, filename, stats);
	set_rights_time(sinfo, stats);
	set_uid_gid_size_links(sinfo, stats);
	sinfo->p_dir_cont = read_and_stat(sinfo, filename);
	sinfo->tree = NULL;
	if (nf == 1)
		sinfo->next = NULL;
}
