/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:45 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/07 23:50:08 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void		print_rec(t_info **sinfo, t_opt opt, t_boolean b)
{
	t_info *tmp;

	tmp = *sinfo;
	if (b == TRUE && tmp->read_and_stat != 0)
		print_blocks(*sinfo, opt);
	while (tmp && tmp->read_and_stat != 0)
	{
		if (!(tmp->filename[0] == '.'))
			write_it_all(tmp, opt);
		if (opt.a == TRUE && (tmp->filename[0] == '.'))
			write_it_all(tmp, opt);
		tmp = tmp->next;
	}
	tmp = *sinfo;
	while (tmp && opt.cr == TRUE)
	{
		if (tmp->tree != NULL && tmp->read_and_stat != 0)
		{
			write(1, "\n", 1);
			write(1, tmp->filepath, ft_strlen(tmp->filepath));
			write(1, ":\n", 2);
			print_rec(&(tmp->tree), opt, TRUE);
		}
		tmp = tmp->next;
	}
}

void		print_blocks(t_info *sinfo, t_opt opt)
{
	int block;

	block = 0;
	if (opt.l != TRUE)
		return ;
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
	if (sinfo->read_and_stat == 0)
		return ;
	if (opt.l == TRUE)
	{
		write(1, sinfo->str_rights, 10);
		write(1, "  ", 2);
		ft_putnbr(sinfo->p_dir_cont);
		ft_putchar('\t');
		write(1, sinfo->user_name, ft_strlen(sinfo->user_name));
		write(1, "  ", 2);
		write(1, sinfo->grp_name, ft_strlen(sinfo->grp_name));
		write(1, "  ", 2);
		write_major_minor(sinfo);
		write(1, " \t", 2);
		write(1, sinfo->date + 4, 12);
		ft_putchar(' ');
		write_pretty_colors(sinfo);
		ft_putchar('\n');
		return ;
	}
	if (sinfo->str_rights[0] == 'd')
		write(1, CYAN, 10);
	write(1, sinfo->filename, ft_strlen(sinfo->filename));
	write(1, FLUSH, 4);
	ft_putchar('\n');
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

void		print_error_perm(char *filename)
{
	write(1, "ls: ", 4);
	write(1, filename, ft_strlen(filename));
	write(1, ": Permission denied", 19);
	write(1, "\n", 1);
}
