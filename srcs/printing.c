/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:45 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/04 00:27:07 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void		print_rec(t_info **sinfo, t_opt opt)
{
	t_info *tmp;

	tmp = *sinfo;
	// if (tmp->next != NULL)
	print_blocks(*sinfo, opt);
	while (tmp)
	{
		//printf("filename>%s<\n", tmp->filename);
		if (opt.a == TRUE && (tmp->filename[0] == '.'))
		{
			write_it_all(tmp, opt);
			tmp = tmp->next;
			continue;
		}
		if (!(tmp->filename[0] == '.'))
			write_it_all(tmp, opt);
		tmp = tmp->next;
	}
	//printf("exit loop\n");
	tmp = *sinfo;
	while (tmp && opt.R == TRUE)
	{
		if (tmp->tree != NULL)
		{
			//printf("i found a LITTLE TREE! [%s]\n", tmp->tree->filename);
			print_rec(&(tmp->tree), opt);
		}
		tmp = tmp->next;
	}
}
void		print_blocks(t_info *sinfo, t_opt opt)
{
	int block;

	block = 0;
	if (opt.l != TRUE)
		return;
	while (sinfo)
	{
		if (opt.a == FALSE && sinfo->filename[0] == '.')
		{
			sinfo = sinfo->next;
			continue;
		}
		block += sinfo->block_cont;
		sinfo = sinfo->next;
	}
	write(1, "total ", 6);
	ft_putnbr(block);
	ft_putchar('\n');
}

void		write_it_all(t_info *sinfo, t_opt opt)
{
	int l;

	if (opt.l == TRUE)
	{
		//write(1, &sinfo->block_cont, 2);
		//write(1, "total ", 6);
		//ft_putnbr(sinfo->dir_cont);
		//write(1, "\n", 1);
		write(1, sinfo->str_rights, 10);
		write(1, "  ", 2);
		ft_putnbr(sinfo->p_dir_cont);
		ft_putchar(' ');
		l = ft_strlen(sinfo->user_name);
		write(1, sinfo->user_name, l);
		write(1, "  ", 2);
		l = ft_strlen(sinfo->grp_name);
		write(1, sinfo->grp_name, l);
		write(1, "  ", 2);
		ft_putnbr(sinfo->bytes);
		ft_putchar(' ');
		l = ft_strlen(sinfo->date);
		write(1, sinfo->date, l);
		ft_putchar(' ');
		//printf("my file type is [%d]\n", sinfo->file_type);
		if (sinfo->file_type == 6)
			write(1, sinfo->linkedfile, ft_strlen(sinfo->linkedfile));
		else
			write(1, sinfo->filename, ft_strlen(sinfo->filename));
		ft_putchar('\n');
		return;
		//l = ft_strlen(sinfo->filename);
		//write(1, sinfo->filename, l);
		//return;
	}
	l = ft_strlen(sinfo->filename);
	write(1, sinfo->filename, l);
	write(1, "\t", 1);
	ft_putchar('\n');
	//printf("\nwhats sinfo? [%s]", sinfo->filename);
//	printf("\n--end write [%d]\n\n\n", l);
}

void		print_errors(char **av)
{
	int			x;
	int			l;
	struct stat	stats;

	x = 1;
	while (av[x])
	{
		if (stat(av[x], &stats) && av[x][0] != '-' && lstat(av[x], &stats))
		{
			write(1, "ls: cannot access '", 19);
			l = ft_strlen(av[x]);
			write(1, av[x], l);
			write(1, "': No such file or directory\n", 29);
		}
		x++;
	}
}

void	print_error_perm(char *filename)
{
	write(1, "ls: ", 4);
	write(1, filename, ft_strlen(filename));
	write(1, ": Permission denied", 19);
	write(1, "\n", 1);
}