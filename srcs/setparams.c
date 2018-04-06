/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:42 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/06 06:28:38 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

t_opt	set_options_zero(char *options)
{
	t_opt opt;

	opt.a = FALSE;
	opt.l = FALSE;
	opt.cr = FALSE;
	opt.r = FALSE;
	opt.t = FALSE;
	if (options != NULL)
	{
		if (ft_strchr(options, 'a'))
			opt.a = TRUE;
		if (ft_strchr(options, 'l'))
			opt.l = TRUE;
		if (ft_strchr(options, 'R'))
			opt.cr = TRUE;
		if (ft_strchr(options, 'r'))
			opt.r = TRUE;
		if (ft_strchr(options, 't'))
			opt.t = TRUE;
	}
	return (opt);
}

void	set_rights_time(t_info *sinfo, struct stat stats)
{
	sinfo->date = (char*)malloc(sizeof(char) * 25);
	ft_strcpy(sinfo->date, ctime(&stats.st_mtime));
	sinfo->date[24] = '\0';
	sinfo->time_sort = stats.st_mtime;
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
	sinfo->device = FALSE;
	if (sinfo->str_rights[0] == 'c')
	{
		sinfo->device = TRUE;
		sinfo->bytes = major(stats.st_rdev);
		sinfo->minor = minor(stats.st_rdev);
	}
}
