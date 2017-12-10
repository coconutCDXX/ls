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
	t_opt	*struct_opt;
	t_info	*struct_info;

	struct_info = (t_info*)malloc(sizeof(*struct_info));
	struct_opt = (t_opt*)malloc(sizeof(*struct_opt));
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
	save_data1(struct_info);
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
	//struct stat stats;
	//struct passwd *person;
	//struct group *grp;
	struct dirent *read;
	DIR *p;
	//char *filename;
	//int	l;

	dir_counter = count_dir();
	p = opendir("./");
	if ((read = readdir(p)) != NULL)
	{
		set_types(&sinfo, read->d_name);
		set_rights(&sinfo, read->d_name);
	}
		// l = strlen(read->d_name);
		// filename = (char*)malloc(sizeof(char) * l + 1);
		// strcpy(d_name, filename);
}

void		set_types(t_info **sinfo, char *filename)
{
	struct stat stats;

	stat(filename, &stats);
	if (S_ISBLK(stats.st_mode))
		*sinfo.file_type = 3;
	if (S_ISCHR(stats.st_mode))
		*sinfo.file_type = 4;
	if (S_ISDIR(stats.st_mode))
		*sinfo.file_type = 2;
	if (S_ISFIFO(stats.st_mode))
		*sinfo.file_type = 5;
	if (S_ISREG(stats.st_mode))
		*sinfo.file_type = 1;
	if (S_ISLNK(stats.st_mode))
		*sinfo.file_type = 6;
}

void		set_rights(t_info **sinfo, char *filename)
{
	 
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
		return 2;
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
