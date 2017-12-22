#include "ls_lib.h"

int		main(int ac, char **av)
{
	char options[6];
	int val_opt;

	if (ac != 1)
	{
		if ((val_opt = verify_options(av, options)) == 1)
		{
			//correct options and possible additional files/dir
			// if 1 read the options and do them
			// check av[etc] and do the options on them
			read_options(ac, av, options);
		}
		else if (val_opt == 0)
		{
			//incorrect option
			printf("if 0 print error incorrect options\n");
		}
		else
		{
			// NO OPTIONS -> check multiple files/dir or errors
			printf("if 2 read the file or dir and print it\n");
			// check av[etc] and print it
		}
	}
	else
	{
		//Basic LS - no options or extra files/dir
		printf("read the current DIR and print basic ls\n");
		read_options(ac, av, NULL);
	}
	return 0;
}

void		read_options(int ac, char **av, char *options)
{
	t_opt	struct_opt;
	t_info	*sinfo;

	sinfo = (t_info*)malloc(sizeof(sinfo));
	if (ft_strchr(options, 'a'))
	struct_opt.opt_a = TRUE;
	if (ft_strchr(options, 'l'))
	struct_opt.opt_l = TRUE;
	if (ft_strchr(options, 'R'))
	struct_opt.opt_R = TRUE;
	if (ft_strchr(options, 'r'))
	struct_opt.opt_r = TRUE;
	if (ft_strchr(options, 't'))
	struct_opt.opt_t = TRUE;
	save_data1(sinfo, "./");
	sort_command(sinfo, struct_opt, av);
}
void		sort_command(t_info *sinfo, t_opt opt, char **av)
{
	int a;

	a = 0;
	if (opt.opt_t == TRUE)
	{
		sort_by_time_xor_rev(&sinfo, opt);
		a = 1;
	}
	if (opt.opt_r == TRUE && a == 1)
		sort_by_r(&sinfo, opt);
	print_rec(&sinfo, opt, av);
	// if R print all else just print
	// if a or l print addition info
}

void		print_rec(t_info **sinfo, t_opt opt, char **av)
{
	t_info *tmp;

	tmp = *sinfo
	while (tmp != NULL)
	{
		if (opt.opt_a == TRUE && (tmp->filename[0] == '.'))
		{
			write_it_all(tmp, opt)
			tmp = tmp->next;
			continue;
		}
		if (!(tmp->filename[0] == '.')
			write_it_all(tmp, opt);
		tmp = tmp->next;
	}
	tmp = *sinfo;
	while (tmp != NULL && opt.opt_R == TRUE)
	{
		if (tmp->tree != NULL)
			print_rec(&(tmp->tree), opt, av);
		tmp = tmp->next;
	}
}

void		write_it_all(t_info *sinfo, t_opt opt)
{
	int l;

	if (opt.opt_l == TRUE)
	{
			write(1, "total ", 6);
			ft_putnbr(sinfo->dir_cont);
			write(1, "\n", 1);
			write(1, sinfo->str_rights, 10);
			ft_putnbr(sinfo->file_type);
			l = strlen(sinfo->user_name);
			write(1, sinfo->user_name, l);
			l = strlen(sinfo->grp_name);
			write(1, sinfo->grp_name, l);
			ft_putnbr(sinfo->bytes);
			l = strlen(sinfo->date);
			write(1, sinfo->date, l);
			l = strlen(sinfo->filename);
			write(1, sinfo->filename, l);
			return;
	}
	l = strlen(sinfo->filename);
	write(1, sinfo->filename, l);
}

void		sort_by_r(t_info **sinfo, t_opt opt)
{
	t_info *newstart;
	t_info *current;
	t_info *saved_new;

	current = *sinfo;
	while (current->next != NULL)
	{
		while (current->next->next != NULL)
			current = current->next;
		if (saved_new == NULL)
		{
			saved_new = current->next;
			newstart = current->next;
			free(current->next);
			current->next = NULL;
		}
		else
		{
			saved_new->next = current->next;
			free(current->next);
			current->next = NULL;
			saved_new = saved_new->next;
		}
		if (opt.opt_R == TRUE && current->tree != NULL)
			sort_by_r(&(sinfo->tree), opt);
		current = *sinfo;
	}
	saved_new->next = current;
	free(current);
	saved_new->next->next = NULL;
	*sinfo = newstart;
}

void		sort_by_time_xor_rev(t_info **sinfo, t_opt opt)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	current = *sinfo;
	start = *sinfo;
	while (curent->next != NULL)
	{
		if (current->time_sort < current->next->time_sort && opt->opt_r == FALSE)
		{
			tmp = curent->next;
			current->next->next = current;
			current = tmp;
			free(tmp);
			current = start;
		}
		else if (current->time_sort > current->next->time_sort && opt->opt_r == TRUE)
		{
			tmp = curent->next;
			current->next->next = current;
			current = tmp;
			free(tmp);
			current = start;
		}
		if (opt.opt_R == TRUE && current->tree != NULL)
			sort_by_time_xor_rev(&(sinfo->tree), opt);
		current = current->next;
	}
}
void		*save_data1(t_info *sinfo, char *filename)
{
	struct stat	stats;
	struct dirent	*read;
	DIR *p;

	sinfo->dir_cont = count_dir();
	p = opendir(filename);
	while ((read = readdir(p)) != NULL)
	{
		set_types_name(sinfo, read->d_name);
		set_rights(sinfo, read->d_name);
		set_uid_gid_size(sinfo, read->d_name);
		set_time(sinfo, read->d_name);
		stat(read->d_name, &stats);
		if (S_ISDIR(stats.st_mode))
		{
			sinfo->tree = (t_info*)malloc(sizeof(s_info));
			save_data1(sinfo.tree, read->d_name);
		}
		else
			sinfo->tree = NULL;
		sinfo->next = (t_info*)malloc(sizeof(s_info));
		sinfo = sinfo->next;
	}
	sinfo->next = NULL;
	closedir(p);
}

void		set_time(t_info *sinfo, char *filename)
{
	struct stat	stats;
	int			l;

	stat(filename, &stats);
	l = strlen(ctime(&stats.st_atime));
	sinfo->date = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->date, ctime(&stats.st_atime));
	sinfo->time_sort = stats.st_atime;
}

void		set_types_name(t_info *sinfo, char *filename)
{
	struct stat stats;
	int l;

	l = strlen(filename);
	sinfo->filename = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->filename, filename);
	stat(filename, &stats);
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
}

void		set_rights(t_info *sinfo, char *filename)
{
	struct stat stats;

	stat(filename, &stats);
	sinfo->str_rights = (char*)malloc(sizeof(char) * 11 + 1);
	switch(sinfo->file_type)
	{
		case 1 :
		sinfo->str_rights[0] = '-';
		case 2 :
		sinfo->str_rights[0] = 'D';
		case 3 :
		sinfo->str_rights[0] = 'B';
		case 4 :
		sinfo->str_rights[0] = 'C';
		case 5 :
		sinfo->str_rights[0] = 'F';
		case 6 :
		sinfo->str_rights[0] = 'L';
	}
	set_rightsbis(sinfo, stats);
}

void		set_rights_USR_GRP(t_info *sinfo, struct stats)
{
	if (stats.st_mode & S_IRUSR)
		sinfo->str_rights[1] = 'r';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IWUSR)
		sinfo->str_rights[1] = 'w';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IXUSR)
		sinfo->str_rights[1] = 'x';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IRGRP)
		sinfo->str_rights[1] = 'r';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IWGRP)
		sinfo->str_rights[1] = 'w';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IXGRP)
		sinfo->str_rights[1] = 'x';
	else
		sinfo->str_rights[1] = '-';
	set_rightstris(sinfo, stats);
}

void		set_rights_OTH(t_info *sinfo, struct stats)
{
	if (stats.st_mode & S_IROTH)
		sinfo->str_rights[1] = 'r';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IWOTH)
		sinfo->str_rights[1] = 'w';
	else
		sinfo->str_rights[1] = '-';
	if (stats.st_mode & S_IXOTH)
		sinfo->str_rights[1] = 'x';
	else
		sinfo->str_rights[1] = '-';
}

void		set_uid_gid_size(t_info *sinfo, char *filename)
{
	struct stat stats;
	struct passwd *person;
	struct group *grp;
	int l;

	stat(filename, &stats);
	person = getpwuid(stats.st_uid);
	l = strlen(person->pw_name);
	sinfo->user_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->user_name, person->pw_name);
	grp = getgrpid(stats.st_gid);
	l = strlen(grp->gr_name);
	sinfo->grp_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->grp_name, grp->gr_name);
	sinfo->bytes = stats.st_size;
}

int		count_dir(void)
{
	DIR *p;
	struct dirent *read;
	int i;

	i = 0;
	p = opendir("./");
	while ((read = readdir(p)) != NULL)
		i++;
	closedir(p);
	return (i);
}
int		valid_options(char o, char *cmp_options)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (o == 'a' || o == 'l' || o == 'R' || o == 'r' || o == 't')
		{
			while (cmp_options[i] != o)
			{
				i++;
				if (i == 5)
					return 1;
			}
			return 2;
		}
		else
			return 0;
	}
	return 0;
}

int		verify_options(char **opt, char *ret)
{
	int i;
	int j;
	int a_v;
	int k;

	i = 0;
	a_v = 0;
	k = 0;
	while (*opt != NULL)
	{
		if (opt[a_v][0] == '-')
		{
			while (opt[a_v][k] != '\0')
			{
				if ((j = valid_options(opt[a_v][k], ret)) == 1)
				{
					ret[i] = opt[a_v][k];
					i++;
					//printf("av currently is: %c and ret is: %s\n", *opt, ret);
				}
				else if (j == 0)
					return 0;
				k++;
			}
			a_v++;
			k = 0;
		}
	}
	printf("the options are: %s\n", ret);
	return 1;
}
