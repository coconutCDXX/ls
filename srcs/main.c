/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:31 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/04 00:30:58 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls_lib.h>

int		main(int ac, char **av)
{
	char	options[6];

	verify_options(av, options);
	//printf("options are [%s]\n", options);
	save_command(ac, av, options);
	return (0);
}

t_opt	set_options_zero(char *options)
{
	t_opt opt;

	opt.a = FALSE;
	opt.l = FALSE;
	opt.R = FALSE;
	opt.r = FALSE;
	opt.t = FALSE;
	if (options != NULL)
	{
		if (ft_strchr(options, 'a'))
			opt.a = TRUE;
		if (ft_strchr(options, 'l'))
			opt.l = TRUE;
		if (ft_strchr(options, 'R'))
			opt.R = TRUE;
		if (ft_strchr(options, 'r'))
			opt.r = TRUE;
		if (ft_strchr(options, 't'))
			opt.t = TRUE;
	}
	return (opt);
}

int		check_av(char **av, int ac)
{
	int		x;

	x = 1;
	while (ac > 1)
	{
		if (av[x][0] != '-')
			return (1);
	//	printf("[%d][%d]\n", x, ac);
		x++;
		ac--;
	}
//	printf("i ret 0\n\n");
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
		//printf("av[x] [%s]\n", av[x]);
		if (!(stat(av[x], &stats)) && (S_ISDIR(stats.st_mode)))
		{
			ret[y] = (char*)malloc(sizeof(char) * ft_strlen(av[x]) + 1);
			ft_strcpy(ret[y], av[x]);
			//printf("folders array ret[%s]\n", ret[y]);
			y++;
		}
		else if ((!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode))) || !(lstat(av[x], &stats)))
			*nf = *nf + 1;
		x++;
	}
	ret[y] = NULL;
	if (ret[0] != NULL)
		sort_folders(ret, opt);
	return (ret);
}

void	save_command(int ac, char **av, char *options)
{
	t_opt	opt;
	t_info	*sinfo;
	char	**folders;

	sinfo = (t_info*)malloc(sizeof(t_info));
	opt = set_options_zero(options);
	// printf("cechk alive\n");
	// printf("opt struct contains a[%d] l[%d] R[%d] r[%d] t[%d]\n", opt.a, opt.l, opt.R, opt.r, opt.t);
	if (check_av(av, ac))
	{
		folders = spec_file(ac, av, opt, sinfo);
		if (folders[0] != NULL)
		{
			save_folders(folders, opt);
			delete_array(folders);
		}
		exit(1);
	}
	save_data1(sinfo, "./", opt.R);
//	printf(" {READ_OPTIONS s_c next} save data is done check for sinfo [%s]\n", sinfo->filename);
	if (sinfo->filename)
		sort_command(sinfo, opt);
	//delete_me(sinfo);
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
	//printf("death--------------------[%d]\n", nonf);
	while (ac > 1)
	{
		//printf("pass b4 alive [%d][%s][%d]\n", ac, av[x], nonf);
		if ((!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode)))
		|| (!(lstat(av[x], &stats)) && !(S_ISDIR(stats.st_mode))))
		{
			save_data2(sinfo, av[x], nonf, totalnf);
			//printf("out of save2\n\n");
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
	{
		sort_command(sinfo, opt);
		//delete_me(sinfo);
	}
}

void	save_folders(char **f, t_opt opt)
{
	int		x;
	t_info	*sinfo;

	x = 0;
	while (f[x])
	{
		sinfo = (t_info*)malloc(sizeof(t_info));
		save_data1(sinfo, f[x], opt.R);
		//printf("SAVE FOLDERS REVIEW [%s] [%s]\n", sinfo->filename, f[x]);
		if (sinfo->filename)
		{
			sort_command(sinfo, opt);
			//delete_me(sinfo);
		}
		sinfo = NULL;
		x++;
	}
}

void	save_data2(t_info *sinfo, char *filename, int nf, int tf)
{
	struct stat stats;

	//printf("!![%d] [%d]!!", tf, nf);
	if (nf < tf)
	{
		//printf("YOU SHALL NOT PASS\n");
		while (nf < tf - 1)
		{
		//	printf("where we at trannies [%s] [%d]\n", sinfo->filename, tf);
			sinfo = sinfo->next;
			tf--;
		}
	//	printf("where we at lovelies [%s] [%d]\n", sinfo->filename, tf);
		sinfo->next = (t_info*)malloc(sizeof(t_info));
		sinfo = sinfo->next;
	}
	if (lstat(filename, &stats) == 0 && (S_ISLNK(stats.st_mode)))
	{
		set_types_name(sinfo, filename, filename, stats);
		set_lstat(sinfo, filename, filename, 0);
		sinfo->p_dir_cont = 1;
		if (nf == 1)
			sinfo->next = NULL;
		sinfo->tree = NULL;
		return;
	}
	stat(filename, &stats);
	//printf("YOU HAVE PASSSED\n");
	set_types_name(sinfo, filename, filename, stats);
	set_rights(sinfo, stats);
	set_uid_gid_size(sinfo, stats);
//	printf("what i crash on?\n");
	set_time(sinfo, stats);
	sinfo->dir_cont = 1;
	sinfo->p_dir_cont = 1;
	sinfo->tree = NULL;
	if (nf == 1)
	{
		sinfo->next = NULL;
		//printf("i nulled\n");
	}
}

void	save_data1(t_info *sinfo, char *filename, boolean b)
{
	struct dirent	*read;
	DIR				*p;
	char			*treename;

	sinfo->dir_cont = count_dir(filename, 'x');
	if (sinfo->dir_cont == 0)
	{
		print_error_perm(filename);
		return ;
	}
	p = opendir(filename);
	while ((read = readdir(p)) != NULL)
	{
		//printf("life!! [%s]\n", read->d_name);
		sinfo->p_dir_cont = 1;
		treename = create_treename(read->d_name, filename);
		set_data(sinfo, treename, read->d_name, b);
		//printf("save_data1[%s][%d]\n", sinfo->filename, sinfo->dir_cont);
		if (sinfo->dir_cont > 1)
		{
			sinfo->next = (t_info*)malloc(sizeof(t_info));
			sinfo->next->dir_cont = sinfo->dir_cont - 1;
			sinfo = sinfo->next;
		}
		else
			sinfo->next = NULL;
		if (treename != read->d_name)
			free(treename);
	}
	closedir(p);
}

char	*create_treename(char *read, char *filename)
{
	char		*ret;

	if (!(ft_strcmp(filename, "./")))
		return (read);
	ret = (char*)malloc(sizeof(char) + ft_strlen(read) + ft_strlen(filename) + 2);
	ft_strcpy(ret, filename);
	ft_strcat(ret, "/");
	ft_strcat(ret, read);
	return (ret);
}

int		count_dir(char *filename, char a)
{
	DIR			*p;
	struct dirent	*read;
	struct stat	stats;
	int			i;
	char			*treename;

	i = 0;
	p = opendir(filename);
	if (p == NULL)
		return (0);
	while ((read = readdir(p)) != NULL)
	{
		treename = create_treename(read->d_name, filename);
		stat(treename, &stats);
		if (a == 'x' || S_ISDIR(stats.st_mode))
		{
			//printf("[%c][%d]+1 its a dir [%s][%s]\n",a , i, filename, read->d_name);
			i++;
			// if (lstat(treename, &stats) == 0 && S_ISLNK(stats.st_mode))
			// {
			// 	//printf("found a link\n");
			// 	i -= 1;
			// }
		}
		//else
		//	printf("[%c] nononononono [%s][%s]\n", a, filename, read->d_name);
		if (treename != read->d_name)
			free(treename);
	}
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
			write(1, "ft_ls: invalid option -- '", 26);
			write(1, &o, 1);
			write(1, "'\nusage: ./ft_ls [-Ralrt] [file ...]\n", 38);
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

// void	ft_putnbr(int n)
// {
// 	if (n == -2147483648)
// 	{
// 		//putstr("-2147483648");
// 		return ;
// 	}
// 	if (n < 0)
// 	{
// 		ft_putchar('-');
// 		n = n * (-1);
// 	}
// 	if (n >= 10)
// 	{
// 		ft_putnbr(n / 10);
// 		ft_putnbr(n % 10);
// 	}
// 	else
// 		ft_putchar(n + 48);
// }
//
// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }
