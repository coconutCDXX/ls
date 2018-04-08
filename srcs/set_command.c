/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:15:59 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/08 00:29:07 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	set_data(t_info *sinfo, char *treename, char *name, t_boolean b)
{
	struct stat		stats;

	if (read_and_stat(sinfo, treename) == 0)
		return ;
	stat(treename, &stats);
	set_types_name(sinfo, treename, name, stats);
	sinfo->filepath = (char*)malloc(sizeof(char) * ft_strlen(treename) + 1);
	ft_strcpy(sinfo->filepath, treename);
	if (sinfo->file_type == 6)
	{
		set_lstat(sinfo, treename, name, b);
		return ;
	}
	set_rights_time(sinfo, stats);
	sinfo->p_dir_cont = 1;
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, 'd');
	set_uid_gid_size(sinfo, stats);
	set_data_tree(sinfo, name, treename, b);
	if (treename != name)
	{
		ft_bzero(treename, ft_strlen(treename));
		free(treename);
	}
}

void	set_data_tree(t_info *sinfo, char *name, char *treename, t_boolean b)
{
	DIR			*p;

	if (sinfo->str_rights[0] == 'd' &&
	(ft_strcmp(name, "..") != 0) && (ft_strcmp(name, ".") != 0) && b == 1)
	{
		if ((p = opendir(treename)) == NULL)
		{
			sinfo->tree = NULL;
			return ;
		}
		closedir(p);
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		save_data1(sinfo->tree, treename, b);
	}
	else
		sinfo->tree = NULL;
}

void	set_lstat(t_info *sinfo, char *treename, char *name, t_boolean b)
{
	struct stat stats;

	lstat(treename, &stats);
	set_rights_time(sinfo, stats);
	sinfo->p_dir_cont = 1;
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, sinfo->str_rights[0]);
	set_uid_gid_size(sinfo, stats);
	set_data_tree(sinfo, name, treename, b);
	if (treename != name)
	{
		ft_bzero(treename, ft_strlen(treename));
		free(treename);
	}
}

void	save_data2_lstat(t_info *sinfo, char *fn, struct stat stats, int nf)
{
	set_types_name(sinfo, fn, fn, stats);
	sinfo->filepath = (char*)malloc(sizeof(char) * ft_strlen(fn) + 1);
	ft_strcpy(sinfo->filepath, fn);
	set_lstat(sinfo, fn, fn, 0);
	if (nf == 1)
		sinfo->next = NULL;
	sinfo->tree = NULL;
}

void	set_types_name(t_info *sinfo, char *fp, char *dname, struct stat stats)
{
	int				l;
	char			*w;

	l = ft_strlen(dname);
	sinfo->file_type = 1;
	sinfo->filename = (char*)malloc(sizeof(char) * ft_strlen(dname) + 1);
	ft_strcpy(sinfo->filename, dname);
	if (lstat(fp, &stats) == 0 && S_ISLNK(stats.st_mode))
	{
		if (stats.st_size == 0)
			stats.st_size = 50;
		sinfo->file_type = 6;
		w = (char*)malloc(sizeof(char) * (stats.st_size + l + 5));
		readlink(fp, w + l + 4, stats.st_size);
		ft_strcpy(w, dname);
		w[l] = ' ';
		w[l + 1] = '-';
		w[l + 2] = '>';
		w[l + 3] = ' ';
		w[l + 4 + stats.st_size] = '\0';
		sinfo->linkedfile = (char*)malloc(sizeof(char) * ft_strlen(w) + 1);
		ft_strcpy(sinfo->linkedfile, w);
		sinfo->linkedfile[ft_strlen(w)] = '\0';
		free(w);
	}
}
