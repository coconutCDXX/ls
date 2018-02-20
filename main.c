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
int		check_av(char **av, int ac)
{
	int x;

	x = 1;
	while (ac > 1)
	{
		if (av[x][0] != '-')
			return 1;
		printf("[%d][%d]\n", x, ac);
		x++;
		ac--;
	}
	printf("i ret 0\n\n");
	return 0;
}

char		**folders_av(int ac, char **av, int *nf, t_opt opt)
{
	int x;
	int y;
	char **ret;
	struct stat stats;

	x = 1;
	y = 0;
	ret = (char**)malloc(sizeof(char*) * ac);
	while (av[x])
	{
		printf("av[x] [%s]\n", av[x]);
		if (!(stat(av[x], &stats)) && (S_ISDIR(stats.st_mode)))
		{
			ret[y] = (char*)malloc(sizeof(char) * strlen(av[x]) + 1);
			strcpy(ret[y], av[x]);
			printf("folders array ret[%s]\n", ret[y]);
			//ret[strlen(av[x])] = NULL;
			y++;
		}
		else if (!(stat(av[x], &stats)) && (!(S_ISDIR(stats.st_mode))))
			*nf = *nf + 1;
		x++;
	}
	sort_folders(ret, opt);
	return (ret);
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
	printf("opt struct contains a[%d] l[%d] R[%d] r[%d] t[%d]\n", opt.a, opt.l, opt.R, opt.r, opt.t);
	if (check_av(av, ac))
		specific_fileread(ac, av, opt, sinfo);
	save_data1(sinfo, "./");

	//quick_memtest(sinfo);
	printf(" {READ_OPTIONS s_c next} save data is done check for sinfo [%s]\n", sinfo->filename);
	sort_command(sinfo, opt);

}
void			specific_fileread(int ac, char **av, t_opt opt, t_info *sinfo)
{
	int x;
	struct stat stats;
	char **folders;
	int nonf;

	x = 1;
	nonf = 0;
	folders = folders_av(ac, av, &nonf, opt);
	printf("death--------------------[%d]\n", nonf);
	while (ac > 1)
	{
		printf("pass b4 alive [%d][%s][%d]\n", ac, av[x], nonf);
		if (av[x][0] != '-')
		{
			if (!(stat(av[x], &stats)))
			{
				if (!(S_ISDIR(stats.st_mode)))
				{
					save_data2(sinfo, av[x], nonf, x);
					printf("out of save2\n\n");
					nonf--;
					// save_data1(sinfo, av[x]);
					// printf("secondary crash report [%s] [%s] [%s]\n", sinfo->filename, sinfo->next->filename,sinfo->next->next->filename);
					// //quick_memtest(sinfo);
				}
			}
			else
			{
				printf("====[%s]==== ERROR\n", av[x]);
				//error go next
			}
		}
		if (ac == 2)
		{
			if (sinfo->filename)
				sort_command(sinfo, opt);
			if (folders != NULL)
				save_folders(folders, opt);
			exit (1);
		}
		ac--;
		x++;
	}
}

void				save_folders(char **f, t_opt opt)
{
	int x;
	t_info	*sinfo;

	x = 0;
	while (f[x])
	{
		sinfo = (t_info*)malloc(sizeof(t_info));
		save_data1(sinfo, f[x]);
		printf("SAVE FOLDERS REVIEW [%s] [%s]\n", sinfo->filename, f[x]);
		sort_command(sinfo, opt);
		free(sinfo);
		sinfo = NULL;
		x++;
	}
}
void				save_data2(t_info *sinfo, char *filename, int nf, int x)
{
	//struct stat		stats;
	//struct dirent	*read;
	//DIR				*p;
	//char			*treename;

	//sinfo->dir_cont = count_dir();
	//p = opendir(filename);
	// while ((read = readdir(p)) != NULL)
	// {
		printf("!![%d] [%d]!!", x, nf);
		if (x > 1)
		{
			printf("YOU SHALL NOT PASS\n");
			while (x > 2)
			{
				printf("where we at trannies [%s] [%d]\n", sinfo->filename, x);
				sinfo = sinfo->next;
				x--;
			}
			printf("where we at trannies [%s] [%d]\n", sinfo->filename, x);
			sinfo->next = (t_info*)malloc(sizeof(t_info));
			sinfo = sinfo->next;
		}
		printf("YOU HAVE PASSSED\n");
		//filename = create_filename(read->d_name, filename);
		set_types_name(sinfo, filename, filename);
		set_rights(sinfo, filename);
		set_uid_gid_size(sinfo, filename);
		printf("what i crash on?\n");
//printf("traveling printf yay f[%s] t[%s] d[%s] s_f[%s] {%s} \n", filename, filename, read->d_name, sinfo->filename, sinfo->str_rights);
		set_time(sinfo, filename);
	//	stat(read->d_name, &stats);
		// if ( sinfo->str_rights[0] == 'd'/*S_ISDIR(stats.st_mode)*/  && read->d_name[0] != '.')
		// {
		// 	printf("tree mode\n");
		// 	sinfo->tree = (t_info*)malloc(sizeof(t_info));
		// 	printf("tree[%s]\n", filename);
		// 	save_data1(sinfo->tree, filename);
		// }
		// else
		sinfo->tree = NULL;
		if (nf == 1)
			sinfo->next = NULL;
	//	sinfo->next = (t_info*)malloc(sizeof(t_info));
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);
	//	sinfo = sinfo->next;
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);


	// }
	//free(sinfo);
	//sinfo->next = NULL;
	//printf("sinfo exist [%p]\n", sinfo);
	//sort_command(sinfo, opt);
	//closedir(p);
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
	printf("acknowledge commander---- save_data1\n\n");
	sinfo->dir_cont = count_dir(filename);
	p = opendir(filename);
	printf("dir count is %d\n", sinfo->dir_cont);
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
		if (sinfo->dir_cont > 1)
		{
			sinfo->next = (t_info*)malloc(sizeof(t_info));
			sinfo->next->dir_cont = sinfo->dir_cont - 1;
			sinfo = sinfo->next;
		}
		else
			sinfo->next = NULL;
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);
		//printf("[%d]--[%s]--[%s]\n", sinfo->dir_cont, sinfo->user_name, sinfo->str_rights);


	}
	//free(sinfo);
	// printf("sinfo? [%s]", sinfo->filename);
	// sinfo = NULL;
	// printf("sinfo exist [%p]\n", sinfo);
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

int		count_dir(char *filename)
{
	DIR *p;
	struct dirent *read;
	int i;

	i = 0;
	p = opendir(filename);
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
