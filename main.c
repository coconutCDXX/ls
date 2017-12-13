#include "ls_lib.h"

int		main(int ac, char **av)
{
	char options[6];
	int val_opt;

	if (ac != 1)
	{
		if ((val_opt = verify_options(av[1], options)) == 1)
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
	}
	return 0;
}

void	read_options(int ac, char **av, char *options)
{
	t_opt	struct_opt;
	t_info	struct_info;

	//struct_info = (t_info)malloc(sizeof(struct_info));
	//struct_opt = (t_opt)malloc(sizeof(struct_opt));
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
	save_data1(&struct_info);
	if (ac == 2)
	{
		printf("do the options on the current DIR\n");
	}
	else
	{
		printf("do the options only on the remaining av[etc]\n");
	}
}
void		save_data1(t_info *sinfo)
{
	int dir_counter;
	struct stat stats;
	struct dirent *read;
	DIR *p;

	dir_counter = count_dir();
	(*sinfo).dir_cont = dir_counter;
	p = opendir("./");
	while ((read = readdir(p)) != NULL)
	{
		set_types_name(sinfo, read->d_name);
		set_rights(sinfo, read->d_name);
		set_uid_gid_size(sinfo, read->d_name);
		set_time(sinfo, read->d_name);
		stat(read->d_name, &stats);
		if (S_ISDIR(stats.st_mode))
		{
			(*sinfo)->tree = (s_info)malloc(sizeof(sinfo));
			save_data2(sinfo, read->d_name);
		}
	}
}

void		set_types_name(t_info *sinfo, char *filename)
{
	struct stat stats;
	int l;

	l = strlen(filename);
	(*sinfo)->filename = (char*)malloc(sizeof(char) * l + 1);
	strcpy((*sinfo)->filename, filename);
	stat(filename, &stats);
	if (S_ISBLK(stats.st_mode))
		(*sinfo).file_type = 3;
	if (S_ISCHR(stats.st_mode))
		(*sinfo).file_type = 4;
	if (S_ISDIR(stats.st_mode))
		(*sinfo).file_type = 2;
	if (S_ISFIFO(stats.st_mode))
		(*sinfo).file_type = 5;
	if (S_ISREG(stats.st_mode))
		(*sinfo).file_type = 1;
	if (S_ISLNK(stats.st_mode))
		(*sinfo).file_type = 6;
}

void		set_rights(t_info *sinfo, char *filename)
{
	struct stat stats;

	stat(filename, &stats);
	(*sinfo)->str_rights = (char*)malloc(sizeof(char) * 11 + 1);
	switch((*sinfo).file_type)
	{
		case 1 :
		(*sinfo)->str_rights[0] = '-';
		case 2 :
		(*sinfo)->str_rights[0] = 'D';
		case 3 :
		(*sinfo)->str_rights[0] = 'B';
		case 4 :
		(*sinfo)->str_rights[0] = 'C';
		case 5 :
		(*sinfo)->str_rights[0] = 'F';
		case 6 :
		(*sinfo)->str_rights[0] = 'L';
	}
	set_rightsbis(sinfo, stats);
}

void		set_rights_USR_GRP(t_info *sinfo, struct stats)
{
	if (stats.st_mode & S_IRUSR)
		(*sinfo)->str_rights[1] = 'r';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IWUSR)
		(*sinfo)->str_rights[1] = 'w';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IXUSR)
		(*sinfo)->str_rights[1] = 'x';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IRGRP)
		(*sinfo)->str_rights[1] = 'r';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IWGRP)
		(*sinfo)->str_rights[1] = 'w';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IXGRP)
		(*sinfo)->str_rights[1] = 'x';
	else
		(*sinfo)->str_rights[1] = '-';
	set_rightstris(sinfo, stats);
}

void		set_rights_OTH(t_info *sinfo, struct stats)
{
	if (stats.st_mode & S_IROTH)
		(*sinfo)->str_rights[1] = 'r';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IWOTH)
		(*sinfo)->str_rights[1] = 'w';
	else
		(*sinfo)->str_rights[1] = '-';
	if (stats.st_mode & S_IXOTH)
		(*sinfo)->str_rights[1] = 'x';
	else
		(*sinfo)->str_rights[1] = '-';
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
	(*sinfo)->user_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy((*sinfo)->user_name, person->pw_name);
	grp = getgrpid(stats.st_gid);
	l = strlen(grp->gr_name);
	(*sinfo)->grp_name = (char*)malloc(sizeof(char) * l + 1);
	strcpy((*sinfo)->grp_name, grp->gr_name);
	(*sinfo).bytes = stats.st_size;
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

int		verify_options(char *opt, char *ret)
{
	int i;
	int j;

	i = 0;
	if (opt[0] != '-')
		return 2;r--
	opt++;
	while (*opt != '\0')
	{
		if ((j = valid_options(*opt, ret)) == 1)
		{
			ret[i] = *opt;
			i++;
			printf("av currently is: %c and ret is: %s\n", *opt, ret);
		}
		else if (j == 0)
			return 0;
		opt++;
	}
	printf("the options are: %s\n", ret);
	return 1;
}
