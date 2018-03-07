/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:31 by cwartell          #+#    #+#             */
/*   Updated: 2018/03/07 03:10:02 by coralie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

int		main(int ac, char **av)
{
	char	options[6];

	verify_options(av, options);
	printf("options are [%s]\n", options);
	read_options(ac, av, options);
	return (0);
}

t_opt	set_options_zero(t_opt struct_opt, char *options)
{
	struct_opt.a = FALSE;
	struct_opt.l = FALSE;
	struct_opt.R = FALSE;
	struct_opt.r = FALSE;
	struct_opt.t = FALSE;
	if (options != NULL)
	{
		if (strchr(options, 'a'))
			struct_opt.a = TRUE;
		if (strchr(options, 'l'))
			struct_opt.l = TRUE;
		if (strchr(options, 'R'))
			struct_opt.R = TRUE;
		if (strchr(options, 'r'))
			struct_opt.r = TRUE;
		if (strchr(options, 't'))
			struct_opt.t = TRUE;
	}
	return (struct_opt);
}

int		check_av(char **av, int ac)
{
	int		x;

	x = 1;
	while (ac > 1)
	{
		if (av[x][0] != '-')
			return (1);
		printf("[%d][%d]\n", x, ac);
		x++;
		ac--;
	}
	printf("i ret 0\n\n");
	return (0);
}

char	**folders_av(int ac, char **av, int *nf, t_opt opt)
{
	int			x;
	int			y;
	char		**ret;
	struct stat	stats;

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
			y++;
		}
		else if (!(stat(av[x], &stats)) && (!(S_ISDIR(stats.st_mode))))
			*nf = *nf + 1;
		x++;
	}
	ret[y] = NULL;
	sort_folders(ret, opt);
	return (ret);
}

void	read_options(int ac, char **av, char *options)
{
	t_opt	opt;
	t_info	*sinfo;
	char	**folders;

	sinfo = (t_info*)malloc(sizeof(t_info));
	opt = set_options_zero(opt, options);
	printf("cechk alive\n");
	printf("opt struct contains a[%d] l[%d] R[%d] r[%d] t[%d]\n", opt.a, opt.l, opt.R, opt.r, opt.t);
	if (check_av(av, ac))
	{
		folders = spec_file(ac, av, opt, sinfo);
		if (folders != NULL)
			save_folders(folders, opt);
		exit(1);
	}
	save_data1(sinfo, "./");
	printf(" {READ_OPTIONS s_c next} save data is done check for sinfo [%s]\n", sinfo->filename);
	sort_command(sinfo, opt);
}

char	**spec_file(int ac, char **av, t_opt opt, t_info *sinfo)
{
	int			x;
	struct stat	stats;
	char		**folders;
	int			totalnf;
	int			nonf;

	x = 1;
	nonf = 0;
	folders = folders_av(ac, av, &nonf, opt);
	totalnf = nonf;
	printf("death--------------------[%d]\n", nonf);
	while (ac > 1)
	{
		printf("pass b4 alive [%d][%s][%d]\n", ac, av[x], nonf);
		if (!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode)))
		{
			save_data2(sinfo, av[x], nonf, totalnf);
			printf("out of save2\n\n");
			nonf--;
		}
		if (ac == 2)
			end_specific_file(sinfo, opt, av);
		ac--;
		x++;
	}
	return (folders);
}

void	end_specific_file(t_info *sinfo, t_opt opt, char **av)
{
	print_errors(av);
	if (sinfo->filename)
		sort_command(sinfo, opt);
}

void	save_folders(char **f, t_opt opt)
{
	int		x;
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

void	save_data2(t_info *sinfo, char *filename, int nf, int tf)
{
	struct stat stats;

	printf("!![%d] [%d]!!", tf, nf);
	if (nf < tf)
	{
		printf("YOU SHALL NOT PASS\n");
		while (nf < tf - 1)
		{
			printf("where we at trannies [%s] [%d]\n", sinfo->filename, tf);
			sinfo = sinfo->next;
			tf--;
		}
		printf("where we at lovelies [%s] [%d]\n", sinfo->filename, tf);
		sinfo->next = (t_info*)malloc(sizeof(t_info));
		sinfo = sinfo->next;
	}
	stat(filename, &stats);
	printf("YOU HAVE PASSSED\n");
	set_types_name(sinfo, filename, filename, stats);
	set_rights(sinfo, stats);
	set_uid_gid_size(sinfo, stats);
	printf("what i crash on?\n");
	set_time(sinfo, stats);
	sinfo->tree = NULL;
	if (nf == 1)
		sinfo->next = NULL;
}

void	save_data1(t_info *sinfo, char *filename)
{
	struct dirent	*read;
	DIR				*p;
	char			*treename;

	printf("acknowledge commander---- save_data1\n\n");
	sinfo->dir_cont = count_dir(filename);
	p = opendir(filename);
	printf("dir count is %d\n", sinfo->dir_cont);
	while ((read = readdir(p)) != NULL)
	{
		treename = create_treename(read->d_name, filename);
		set_data(sinfo, treename, read->d_name);
		if (sinfo->dir_cont > 1)
		{
			sinfo->next = (t_info*)malloc(sizeof(t_info));
			sinfo->next->dir_cont = sinfo->dir_cont - 1;
			sinfo = sinfo->next;
		}
		else
			sinfo->next = NULL;
	}
	closedir(p);
}

char	*create_treename(char *read, char *filename)
{
	char		*ret;

	if (!(strcmp(filename, "./")))
		return (read);
	ret = (char*)malloc(sizeof(char) + strlen(read) + strlen(filename) + 2);
	strcpy(ret, filename);
	strcat(ret, "/");
	strcat(ret, read);
	return (ret);
}

int		count_dir(char *filename)
{
	DIR				*p;
	struct dirent	*read;
	int				i;

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
					return (1);
			}
			return (0);
		}
		else
		{
			write(1, "ls: invalid option -- '", 23);
			write(1, &o, 1);
			write(1, "'\nTry 'ls --help' for more information\n", 39);
			exit(1);
		}
	}
	return (0);
}

void	verify_options(char **av, char *ret)
{
	int i;
	int a_v;
	int k;

	i = 0;
	a_v = 1;
	k = 1;
	while (av[a_v])
	{
		while (av[a_v][k] != '\0' && av[a_v][0] == '-')
		{
			if (valid_options(av[a_v][k], ret))
			{
				ret[i] = av[a_v][k];
				i++;
			}
			k++;
		}
		k = 1;
		a_v++;
	}
	ret[i] = '\0';
}

void	ft_putnbr(int n)
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
