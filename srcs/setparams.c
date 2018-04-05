/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:42 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/04 22:03:43 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	set_data(t_info *sinfo, char *treename, char *name, boolean b)
{
	struct stat		stats;

	stat(treename, &stats);
	set_types_name(sinfo, treename, name, stats);
	if (sinfo->file_type == 6)
	{
		set_lstat(sinfo, treename, name, b);
		//printf("set_data{%s}\n", sinfo->filename);
		return;
	}
	set_rights(sinfo, stats);
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, 'd');
	set_uid_gid_size(sinfo, stats);
	set_time(sinfo, stats);
	if (sinfo->str_rights[0] == 'd' &&
	(ft_strcmp(name, "..") != 0) && (ft_strcmp(name, ".") != 0) && b == 1)
	{
		//printf("tree mode\n");
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		//printf("tree[%s]\n", treename);
		save_data1(sinfo->tree, treename, b);
	}
	else
		sinfo->tree = NULL;
	//printf("set_data{%s}\n", sinfo->filename);
}

void	set_lstat(t_info *sinfo, char *treename, char *name, boolean b)
{
	struct stat stats;

	lstat(treename, &stats);
	// set_types_name()
	set_rights(sinfo, stats);
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, sinfo->str_rights[0]);
	set_uid_gid_size(sinfo, stats);
	set_time(sinfo, stats);
	if (sinfo->str_rights[0] == 'd'
	&& (ft_strcmp(name, "..") != 0) && (ft_strcmp(name, ".") != 0) && b == 1)
	{
		//printf("tree mode\n");
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		//printf("tree[%s]\n", treename);
		save_data1(sinfo->tree, treename, b);
	}
	else
		sinfo->tree = NULL;
}

void	set_time(t_info *sinfo, struct stat stats)
{
//	int			l;

	//l = ft_strlen(ctime(&stats.st_mtime));
	sinfo->date = (char*)malloc(sizeof(char) * 25);
	ft_strcpy(sinfo->date, ctime(&stats.st_mtime));
	sinfo->date[24] = '\0';
	sinfo->time_sort = stats.st_mtime;
}

void	set_types_name(t_info *sinfo, char *filename, char *dname, struct stat stats)
{
	int			l;
	//int			k;
	long long int ls;
	char			*w;
//char			*rl;

	l = ft_strlen(dname);
	sinfo->file_type = 1;
	sinfo->filename = (char*)malloc(sizeof(char) * l + 1);
	ft_strcpy(sinfo->filename, dname);
	//printf("filename (%s)\n", sinfo->filename);
	if (lstat(filename, &stats) == 0 && S_ISLNK(stats.st_mode))
	{
		sinfo->file_type = 6;
		//rl = (char*)malloc(sizeof(char) * stats.st_size);
		//printf("this is a link [%s]\n", dname);
		w = (char*)malloc(sizeof(char) * (stats.st_size + l + 5));
		ls = readlink(filename, w + l + 4, stats.st_size);
			//k = ft_strlen(rl);
		//printf("stats.st_size [%lld](%lld)[%lld] {%s}\n", ls, ls, stats.st_size, filename);

			//printf("[%s] [%lld] [%ld] pointee\n", w, stats.st_size , (long int)l + 5);
		//memmove(w + l + 4, w, stats.st_size);
			//printf("[%p] [%p]filename [%s][%lu]\n", w + l + 4, w, w, ft_strlen(w));
			//printf("null terminated filename [%s]\n", w);
		ft_strcpy(w, dname);
			//printf("w.o end filename [%s]\n", w);
		w[l] = ' ';
		w[l + 1] = '-';
		w[l + 2] = '>';
		w[l + 3] = ' ';
		//strncat(w, rl, ls);
		w[l + 4 + stats.st_size] = '\0';
			//printf("final filename [%s][%lu]\n", w, ft_strlen(w));
		sinfo->linkedfile = (char*)malloc(sizeof(char) * ft_strlen(w) + 1);
		ft_strcpy(sinfo->linkedfile, w);
		sinfo->linkedfile[ft_strlen(w)] = '\0';
		free(w);
		//printf("sinfo[%s]\n", sinfo->linkedfile);
		//free(rl);
	}
	//printf("sinfo->file_type [%s] [%s] [%d]\n", filename, sinfo->filename, sinfo->file_type);
}

void	set_rights(t_info *sinfo, struct stat stats)
{
	sinfo->str_rights = (char*)malloc(sizeof(char) * 11);
	sinfo->str_rights[0] = '-';
	if (sinfo->file_type == 6)
		sinfo->str_rights[0] = 'l';
	if (S_ISDIR(stats.st_mode))
		sinfo->str_rights[0] = 'd';
	if (S_ISBLK(stats.st_mode))
		sinfo->str_rights[0] = 'b';
	if (S_ISCHR(stats.st_mode))
		sinfo->str_rights[0] = 'c';
	if (S_ISFIFO(stats.st_mode))
		sinfo->str_rights[0] = 'p';
	if (S_ISSOCK(stats.st_mode))
		sinfo->str_rights[0] = 's';
	set_rights_usr_grp(sinfo, stats);
}

void	set_rights_usr_grp(t_info *sinfo, struct stat stats)
{
	if (stats.st_mode & S_IRUSR)
		sinfo->str_rights[1] = 'r';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IWUSR)
		sinfo->str_rights[2] = 'w';
	else
		sinfo->str_rights[2] = '-';
	if (stats.st_mode & S_IXUSR)
		sinfo->str_rights[3] = 'x';
	else
		sinfo->str_rights[3] = '-';
	if (stats.st_mode & S_IRGRP)
		sinfo->str_rights[4] = 'r';
	else
		sinfo->str_rights[4] = '-';
	if (stats.st_mode & S_IWGRP)
		sinfo->str_rights[5] = 'w';
	else
		sinfo->str_rights[5] = '-';
	set_rights_oth(sinfo, stats);
}

void	set_rights_oth(t_info *sinfo, struct stat stats)
{
	if (stats.st_mode & S_IXGRP)
		sinfo->str_rights[6] = 'x';
	else
		sinfo->str_rights[6] = '-';
	if (stats.st_mode & S_IROTH)
		sinfo->str_rights[7] = 'r';
	else
		sinfo->str_rights[7] = '-';
	if (stats.st_mode & S_IWOTH)
		sinfo->str_rights[8] = 'w';
	else
		sinfo->str_rights[8] = '-';
	if (stats.st_mode & S_IXOTH)
		sinfo->str_rights[9] = 'x';
	else
		sinfo->str_rights[9] = '-';
	sinfo->str_rights[10] = '\0';
}

void	set_uid_gid_size(t_info *sinfo, struct stat stats)
{
	struct passwd	*person;
	struct group	*grp;
	int				l;

	sinfo->block_cont = (int)stats.st_blocks;
	person = getpwuid(stats.st_uid);
	l = ft_strlen(person->pw_name);
	sinfo->user_name = (char*)malloc(sizeof(char) * l + 1);
	ft_strcpy(sinfo->user_name, person->pw_name);
	grp = getgrgid(stats.st_gid);
	l = ft_strlen(grp->gr_name);
	sinfo->grp_name = (char*)malloc(sizeof(char) * l + 1);
	ft_strcpy(sinfo->grp_name, grp->gr_name);
	sinfo->bytes = stats.st_size;
}
