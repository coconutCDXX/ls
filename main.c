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

t_opt	set_options_zero(t_opt struct_opt)
{
	struct_opt.a = FALSE;

	struct_opt.l = FALSE;

	struct_opt.R = FALSE;

	struct_opt.r = FALSE;

	struct_opt.t = FALSE;
	return (struct_opt);
}

void		read_options(int ac, char **av, char *options)
{
	t_opt	opt;
	t_info	*sinfo;

	sinfo = (t_info*)malloc(sizeof(t_info));
	opt = set_options_zero(opt);
	if (options != NULL)
	{
		if (strchr(options, 'a'))
			opt.a = TRUE;
		if (strchr(options, 'l'))
		 	opt.l = TRUE;
		if (strchr(options, 'R'))
			opt.R = TRUE;
		if (strchr(options, 'r'))
			opt.r = TRUE;
		if (strchr(options, 't'))
			opt.t = TRUE;
	}
	printf("cechk alive\n");
	if (ac >= 2)
		specific_fileread(ac, av, opt, sinfo);
	printf("opt struct contains a[%d] l[%d] R[%d] r[%d] t[%d]\n", opt.a, opt.l, opt.R, opt.r, opt.t);
	save_data1(sinfo, "./");

	quick_memtest(sinfo);
	printf(" {READ_OPTIONS s_c next} save data is done check for sinfo [%s]\n", sinfo->filename);
	sort_command(sinfo, opt, av);

}
void	specific_fileread(int ac, char **av, t_opt opt, t_info *sinfo)
{
	int x;
	struct stat stats;

	x = 1;
	if (ac > 1)
	{
		while (ac > 1)
		{
			printf("pass b4 alive [%d][%s]\n", ac, av[x]);
			if (av[x][0] != '-')
			{
				if (!(stat(av[x], &stats)))
				{
					printf("specific check[%s]\n", av[x]);
					save_data1(sinfo, av[x]);
					quick_memtest(sinfo);
					sort_command(sinfo, opt, av);
				}
			}
			ac--;
			x++;
		}
	}
}

void quick_memtest(t_info *sinfo)
{
	int i = 0;

	while (sinfo)
	{
		printf("{%s} %d\n", sinfo->filename, i);
		i++;
		if (i == 20)
			sinfo->next = NULL;
		sinfo = sinfo->next;
	}
}
void		print_rec(t_info **sinfo, t_opt opt, char **av)
{
	t_info *tmp;

	tmp = *sinfo;
	printf("is tmp alive? [%s]\n", tmp->filename);
	while (tmp)
	{
		printf("printing -> [%s][%d]\n", tmp->filename, (int)strlen(tmp->filename));
		if (opt.a == TRUE && (tmp->filename[0] == '.'))
		{
			write_it_all(tmp, opt);
			tmp = tmp->next;
			continue;
		}
		if (!(tmp->filename[0] == '.'))
		{
			write_it_all(tmp, opt);
		}
		tmp = tmp->next;
		printf("[%p]\n\n", tmp);
	}
	printf("exit loop\n");
	tmp = *sinfo;
	while (tmp->next != NULL && opt.R == TRUE)
	{
		if (tmp->tree != NULL)
			print_rec(&(tmp->tree), opt, av);
		tmp = tmp->next;
	}
}

void		write_it_all(t_info *sinfo, t_opt opt)
{
	int l;

	if (opt.l == TRUE)
	{
			//write(1, "total ", 6);
			// ft_putnbr(sinfo->dir_cont);
			// write(1, "\n", 1);
			write(1, sinfo->str_rights, 10);
			ft_putchar(' ');
			ft_putnbr(sinfo->file_type);
			ft_putchar(' ');
			l = strlen(sinfo->user_name);
			write(1, sinfo->user_name, l);
			ft_putchar(' ');
			l = strlen(sinfo->grp_name);
			write(1, sinfo->grp_name, l);
			ft_putchar('\t');
			ft_putnbr(sinfo->bytes);
			ft_putchar(' ');
			l = strlen(sinfo->date);
			write(1, sinfo->date, l);
			ft_putchar(' ');
			// l = strlen(sinfo->filename);
			// write(1, sinfo->filename, l);
			// return;
	}
	l = strlen(sinfo->filename);
	write(1, sinfo->filename, l);
	//printf("\nwhats sinfo? [%s]", sinfo->filename);
	printf("--end write [%d]\n", l);
}

void		sort_command(t_info *sinfo, t_opt opt, char **av)
{
	sort_by_alpha(&sinfo);
	if (opt.t == TRUE)
	{
		sort_by_time_xor_rev(&sinfo, opt);
		printf("i sorted by t\n");
	}
	if (opt.r == TRUE)
		sort_by_r(&sinfo, opt);
	printf("sort_command is sinfo alive? [%s]\n", sinfo->filename);
	print_rec(&sinfo, opt, av);
	// if R print all else just print
	// if a or l print addition info
}

void		sort_by_r(t_info **sinfo, t_opt opt)
{
	t_info *newstart;
	t_info *current;
	t_info *saved_new;

	current = *sinfo;
	newstart = *sinfo;
	while (current->next != NULL)
	{
		while (current->next->next)
		{
			printf("next next [%p] next [%s][%p]\n",current->next->next, current->next->filename, current->next);
			current = current->next;
		}
		printf("current is [%s]\n", current->filename);
		if (newstart == *sinfo)
		{
			saved_new = current->next;
			newstart = current->next;
			newstart->next = saved_new;
			//free(current->next);
			current->next = NULL;
			printf("new start [%s] [%p]\n", saved_new->filename, current->next);
		}
		else
		{
			saved_new->next = current->next;
			//free(current->next);
			current->next = NULL;

			saved_new = saved_new->next;
			printf("saved_new->next [%s]\n", saved_new->filename);
		}
		if (opt.R == TRUE && current->tree != NULL)
			sort_by_r(&(current->tree), opt);
		current = *sinfo;
	}
	saved_new->next = current;
	//free(current);
	saved_new->next->next = NULL;
	*sinfo = newstart;
}
void			sort_by_alpha(t_info **sinfo)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		//printf("stats of cur [%s]\n", current->filename);
		if (check_alpha(current->filename, current->next->filename))
		{
			tmp = current->next;
			current->next = tmp->next;
			tmp->next = current;
			if (*sinfo == current)
			{
				*sinfo = tmp;
				current = *sinfo;
			}
			else
			{
				start->next = tmp;
				current = *sinfo;
			}
		}
		else
		{
			start = current;
			current = current->next;
		}
		// if (current->tree != NULL)
		// {
		// 	printf("tree mode fuck up\n");
		// 	sort_by_alpha(&(current->tree));
		// }
	}
}

int		check_alpha(char *a, char *b)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if(!(strcmp(b, "..")) && !(strcmp(a, ".")))
		return 0;
	if (a[j] == '.')
		j++;
	if (b[i] == '.')
		i++;
	if (a[j] >= 65 && a[j] <= 90 && !(b[i] >= 65 && b[i] <= 90))
	{	if (a[j] + 32 > b[i])
			return (1);
		else
			return (0);
		}
	if (b[i] >= 65 && b[i] <= 90 && !(a[j] >= 65 && a[j] <= 90))
		{if (b[i] + 32 < a[j])
			return (1);
		else
			return (0);
		}
	if (a[j] > b[i])
		return (1);
	if (a[j] == b[i])
		return (check_alpha(a + 1, b + 1));
	return (0);
}
void		sort_by_time_xor_rev(t_info **sinfo, t_opt opt)
{
	t_info *current;
	t_info *tmp;
	t_info *start;

	start = *sinfo;
	current = *sinfo;
	while (current->next)
	{
		printf("where are we [%s] [%lld]\n", current->filename, (long long)current->time_sort);
		//printf("next one [%s] [%lld]\n\n", current->next->filename, (long long)current->next->time_sort);
		if (current->time_sort < current->next->time_sort)
		{
			tmp = current->next;
			current->next = tmp->next;
			tmp->next = current;
			if (*sinfo == current)
			{
				*sinfo = tmp;
				current = *sinfo;
				printf("new start![%s]\n", current->filename);
			}
			else
			{
				start->next = tmp;
				current = *sinfo;
				printf("in the sort part a [%s] [%lld]\n", start->filename, (long long)current->time_sort);
				printf("in the sort part b [%s] [%lld]\n\n", start->next->filename, (long long)current->next->time_sort);
			}
		}
		else
		{
			start = current;
			current = current->next;
			printf("aliv?\n");
		}
		// else if (current->time_sort > current->next->time_sort && opt.r == TRUE)
		// {
		// 	printf("this is happening?\n");
		// 	tmp = current->next;
		// 	current->next->next = current;
		// 	current = tmp;
		// 	free(tmp);
		// 	current = *sinfo;
		// 	continue;
		// }
		// if (opt.R == TRUE && current->tree != NULL)
		// 	sort_by_time_xor_rev(&(current->tree), opt);
	}
	//*sinfo = start;
	printf("whats the new start [%s]\n", start->filename);
}

void		save_data1(t_info *sinfo, char *filename)
{
	struct stat		stats;
	struct dirent	*read;
	DIR				*p;
	char			*treename;
	//t_info			*start;
	//t_info			*tmp;

	//start = *sinfo;
	//tmp = *sinfo;
	sinfo->dir_cont = count_dir();
	p = opendir(filename);

	while ((read = readdir(p)) != NULL)
	{
		treename = create_treename(read->d_name, filename);
		set_types_name(sinfo, treename, read->d_name);
		set_rights(sinfo, treename);
		set_uid_gid_size(sinfo, treename);
		printf("what i crash on?\n");
//printf("traveling printf yay f[%s] t[%s] d[%s] s_f[%s] {%s} \n", filename, treename, read->d_name, sinfo->filename, sinfo->str_rights);
		set_time(sinfo, treename);
		stat(read->d_name, &stats);
		if ( sinfo->str_rights[0] == 'd'/*S_ISDIR(stats.st_mode)*/  && read->d_name[0] != '.')
		{
			printf("tree mode\n");
			sinfo->tree = (t_info*)malloc(sizeof(t_info));
			printf("tree[%s]\n", treename);
			save_data1(sinfo->tree, treename);
		}
		else
			sinfo->tree = NULL;
		sinfo->next = (t_info*)malloc(sizeof(t_info));
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);
		sinfo = sinfo->next;
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);


	}
	//free(sinfo);
	sinfo = NULL;
	printf("sinfo exist [%p]\n", sinfo);
	closedir(p);
}

char		*create_treename(char *read, char *filename)
{
	//char *ret;
	char		*ret;

	if (!(strcmp(filename, "./")))
	{
	// 	ret = (char*)malloc(sizeof(char) * strlen(read) + 1);
	// 	//ret[0] = '/';
	// 	//ret[1] = '/';
	// 	strcat(ret, read);
		return read;
	}
	ret = (char*)malloc(sizeof(char) + strlen(read) + strlen(filename) + 2);
	strcpy(ret, filename);
	strcat(ret, "/");
	strcat(ret, read);
	//strcat(ret, "/");
	return ret;
}

void		set_time(t_info *sinfo, char *filename)
{
	struct stat	stats;
	int			l;

	stat(filename, &stats);
	l = strlen(ctime(&stats.st_mtime));
	sinfo->date = (char*)malloc(sizeof(char) * l + 1);
	strcpy(sinfo->date, ctime(&stats.st_mtime));
	sinfo->time_sort = stats.st_mtime;
}

void		set_types_name(t_info *sinfo, char *filename, char *dname)
{
	struct stat stats;
	int l;
	int k;

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

void		set_rights(t_info *sinfo, char *filename)
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
	set_rights_USR_GRP(sinfo, stats);
}

void		set_rights_USR_GRP(t_info *sinfo, struct stat stats)
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
	if (stats.st_mode & S_IXGRP)
		sinfo->str_rights[6] = 'x';
	else
		sinfo->str_rights[6] = '-';
	set_rights_OTH(sinfo, stats);
}

void		set_rights_OTH(t_info *sinfo, struct stat stats)
{
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
	grp = getgrgid(stats.st_gid);
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

int		verify_options(char **av, char *ret)
{
	int i;
	int j;
	int a_v;
	int k;

	i = 0;
	a_v = 1;
	k = 1;
	while (av[a_v])
	{
		if (av[a_v][0] == '-')
		{
			while (av[a_v][k] != '\0')
			{
				if ((j = valid_options(av[a_v][k], ret)) == 1)
				{
					ret[i] = av[a_v][k];
					i++;
					//printf("av currently is: %c and ret is: %s\n", *av, ret);
				}
				else if (j == 0)
					return 0;
				k++;
			}
			k = 1;
		}
		a_v++;
	}
	ret[i] = '\0';
	//printf("the options are: %s\n", ret);
	return 1;
}

void		ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		//putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = n * (-1);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}
