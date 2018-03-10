/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:42 by cwartell          #+#    #+#             */
/*   Updated: 2018/03/09 04:19:43 by coralie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	set_data(t_info *sinfo, char *treename, char *name)
{
	struct stat		stats;

	stat(treename, &stats);
	set_types_name(sinfo, treename, name, stats);
	if (sinfo->file_type == 6)
	{
		set_lstat(sinfo, treename, name);
		return;
	}
	set_rights(sinfo, stats);
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, sinfo->str_rights[0]);
	set_uid_gid_size(sinfo, stats);
	set_time(sinfo, stats);
	if (sinfo->str_rights[0] == 'd' && (strcmp(name, "..") != 0) && (strcmp(name, ".") != 0))
	{
		printf("tree mode\n");
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		printf("tree[%s]\n", treename);
		save_data1(sinfo->tree, treename);
	}
	else
		sinfo->tree = NULL;
}

void	set_lstat(t_info *sinfo, char *treename, char *name)
{
	struct stat stats;

	lstat(treename, &stats);
	set_rights(sinfo, stats);
	if (sinfo->str_rights[0] == 'd')
		sinfo->p_dir_cont = count_dir(treename, sinfo->str_rights[0]);
	set_uid_gid_size(sinfo, stats);
	set_time(sinfo, stats);
	if (sinfo->str_rights[0] == 'd' && (strcmp(name, "..") != 0) && (strcmp(name, ".") != 0))
	{
		printf("tree mode\n");
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		printf("tree[%s]\n", treename);
		save_data1(sinfo->tree, treename);
	}
	else
		sinfo->tree = NULL;
}

void	set_time(t_info *sinfo, struct stat stats)
{
	int			l;

	l = strlen(ctime(&stats.st_mtime));
	sinfo->date = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->date, ctime(&stats.st_mtime));
	sinfo->time_sort = stats.st_mtime;
}

void	set_types_name(t_info *sinfo, char *filename, char *dname, struct stat stats)
{
	int			l;
	char			*w;

	l = strlen(dname);
	if (lstat(filename, &stats) == 0 && S_ISLNK(stats.st_mode))
	{
		sinfo->file_type = 6;
		w = (char*)malloc(sizeof(char) * (stats.st_size + l + 5));
		readlink(filename, w, stats.st_size);
		printf("[%s] [%ld] [%ld] pointee\n", w, stats.st_size , (long int)l + 5);
		memmove(w + l + 4, w, stats.st_size);
		printf("[%p] [%p]filename [%s][%lu]\n", w + l + 4, w, w, strlen(w));
		w[l + 4 + stats.st_size] = '\0';
		printf("null terminated filename [%s]\n", w);
		strcpy(w, dname);
		printf("w.o end filename [%s]\n", w);
		w[l] = ' ';
		w[l + 1] = '-';
		w[l + 2] = '>';
		w[l + 3] = ' ';
		printf("final filename [%s][%lu]\n", w, strlen(w));
		sinfo->linkedfile = (char*)malloc(sizeof(char) * strlen(w) + 1);
		strcpy(sinfo->linkedfile, w);
		sinfo->linkedfile[strlen(w)] = '\0';
	}
	sinfo->file_type = (sinfo->file_type == 6 ? 6 : 1);
	sinfo->filename = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->filename, dname);
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
	l = strlen(person->pw_name);
	sinfo->user_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->user_name, person->pw_name);
	grp = getgrgid(stats.st_gid);
	l = strlen(grp->gr_name);
	sinfo->grp_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->grp_name, grp->gr_name);
	sinfo->bytes = stats.st_size;
}
