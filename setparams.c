/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:42 by cwartell          #+#    #+#             */
/*   Updated: 2018/02/28 15:27:57 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void	set_data(t_info *sinfo, char *treename, char *name)
{
	struct stat		stats;

	set_types_name(sinfo, treename, name);
	set_rights(sinfo, treename);
	set_uid_gid_size(sinfo, treename);
	set_time(sinfo, treename);
	stat(name, &stats);
	if (sinfo->str_rights[0] == 'd'
	&& (strcmp(name, "..") != 0) && (strcmp(name, ".") != 0))
	{
		printf("tree mode\n");
		sinfo->tree = (t_info*)malloc(sizeof(t_info));
		printf("tree[%s]\n", treename);
		save_data1(sinfo->tree, treename);
	}
	else
		sinfo->tree = NULL;
}

void	set_time(t_info *sinfo, char *filename)
{
	struct stat	stats;
	int			l;

	stat(filename, &stats);
	l = strlen(ctime(&stats.st_mtime));
	sinfo->date = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->date, ctime(&stats.st_mtime));
	sinfo->time_sort = stats.st_mtime;
}

void	set_types_name(t_info *sinfo, char *filename, char *dname)
{
	struct stat	stats;
	int			l;
	int			k;

	l = strlen(dname);
	sinfo->filename = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->filename, dname);
	k = stat(filename, &stats);
	if (S_ISBLK(stats.st_mode))
		sinfo->file_type = 3;
	if (S_ISCHR(stats.st_mode))
		sinfo->file_type = 4;
	if (S_ISDIR(stats.st_mode))
		sinfo->file_type = 2;
	if (S_ISFIFO(stats.st_mode))
		sinfo->file_type = 5;
	if (S_ISREG(stats.st_mode))
		sinfo->file_type = 1;
	if (S_ISLNK(stats.st_mode))
		sinfo->file_type = 6;
	printf("sinfo->file_type [%d] [%d]\n", sinfo->file_type, k);
	if (k == -1)
		perror("Error: ");
}

void	set_rights(t_info *sinfo, char *filename)
{
	struct stat stats;

	stat(filename, &stats);
	sinfo->str_rights = (char*)malloc(sizeof(char) * 11);
	if (sinfo->file_type == 1)
		sinfo->str_rights[0] = '-';
	if (sinfo->file_type == 2)
		sinfo->str_rights[0] = 'd';
	if (sinfo->file_type == 3)
		sinfo->str_rights[0] = 'b';
	if (sinfo->file_type == 4)
		sinfo->str_rights[0] = 'c';
	if (sinfo->file_type == 5)
		sinfo->str_rights[0] = 'f';
	if (sinfo->file_type == 6)
		sinfo->str_rights[0] = 'l';
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

void	set_uid_gid_size(t_info *sinfo, char *filename)
{
	struct stat		stats;
	struct passwd	*person;
	struct group	*grp;
	int				l;

	stat(filename, &stats);
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
