/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:24:05 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 02:32:00 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

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
		if (!(stat(av[x], &stats)) && (S_ISDIR(stats.st_mode)))
		{
			ret[y] = (char*)malloc(sizeof(char) * ft_strlen(av[x]) + 1);
			ft_strcpy(ret[y], av[x]);
			y++;
		}
		else if ((!(stat(av[x], &stats)) && !(S_ISDIR(stats.st_mode)))
		|| !(lstat(av[x], &stats)))
			*nf = *nf + 1;
		x++;
	}
	ret[y] = NULL;
	if (ret[0] != NULL)
		sort_folders(ret, opt);
	return (ret);
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
		if (sinfo->filename)
			sort_command(sinfo, opt);
		sinfo = NULL;
		x++;
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
		sinfo->p_dir_cont = 1;
		treename = create_treename(read->d_name, filename);
		set_data(sinfo, treename, read->d_name, b);
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
	ret = (char*)malloc(sizeof(char) *
	(ft_strlen(read) + ft_strlen(filename) + 2));
	ft_strcpy(ret, filename);
	ft_strcat(ret, "/");
	ft_strcat(ret, read);
	return (ret);
}

int		count_dir(char *filename, char a)
{
	DIR				*p;
	struct dirent	*read;
	struct stat		stats;
	int				i;
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
			i++;
		if (treename != read->d_name)
			free(treename);
	}
	closedir(p);
	return (i);
}
