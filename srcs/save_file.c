/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:26:53 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 02:27:48 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

char	**spec_file(int ac, char **av, t_opt opt, t_info *sinfo)
{
	int			x;
	struct stat	stats;
	char		**folders;
	int			totalnf;
	int			nonf;

	x = 1;
	nonf = 0;
	folders = folders_av(ac, av, &nonf, opt);
	totalnf = nonf;
	while (ac > 1)
	{
		if ((!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode)))
		|| (!(lstat(av[x], &stats)) && !(S_ISDIR(stats.st_mode))))
		{
			save_data2(sinfo, av[x], nonf, totalnf);
			nonf--;
		}
		if (ac == 2)
			end_specific_file(sinfo, opt, av);
		ac--;
		x++;
	}
	return (folders);
}

void	end_specific_file(t_info *sinfo, t_opt opt, char **av)
{
	print_errors(av);
	if (sinfo->filename)
	{
		sort_command(sinfo, opt);
	}
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
	if (lstat(filename, &stats) == 0 && (S_ISLNK(stats.st_mode)))
	{
		set_types_name(sinfo, filename, filename, stats);
		set_lstat(sinfo, filename, filename, 0);
		sinfo->p_dir_cont = 1;
		if (nf == 1)
			sinfo->next = NULL;
		sinfo->tree = NULL;
		return ;
	}
	stat(filename, &stats);
	set_types_name(sinfo, filename, filename, stats);
	set_rights_time(sinfo, stats);
	set_uid_gid_size(sinfo, stats);
	//set_time(sinfo, stats);
	sinfo->dir_cont = 1;
	sinfo->p_dir_cont = 1;
	sinfo->tree = NULL;
	if (nf == 1)
		sinfo->next = NULL;
}
