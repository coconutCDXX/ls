/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:45 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 01:57:07 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void		print_rec(t_info **sinfo, t_opt opt)
{
	t_info *tmp;

	tmp = *sinfo;
	print_blocks(*sinfo, opt);
	while (tmp)
	{
		if (!(tmp->filename[0] == '.'))
			write_it_all(tmp, opt);
		if (opt.a == TRUE && (tmp->filename[0] == '.'))
			write_it_all(tmp, opt);
		tmp = tmp->next;
	}
	tmp = *sinfo;
	while (tmp && opt.R == TRUE)
	{
		if (tmp->tree != NULL)
		{
			write(1, "\n./", 3);
			write(1, tmp->filepath, ft_strlen(tmp->filepath));
			write(1, "\n", 1);
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
	if (opt.l == TRUE)
	{
		write(1, sinfo->str_rights, 10);
		write(1, "  ", 2);
		ft_putnbr(sinfo->p_dir_cont);
		ft_putchar(' ');
		write(1, sinfo->user_name, ft_strlen(sinfo->user_name));
		write(1, "  ", 2);
		write(1, sinfo->grp_name, ft_strlen(sinfo->grp_name));
		write(1, "  ", 2);
		ft_putnbr(sinfo->bytes);
		write(1, "    ", 4);
		write(1, sinfo->date + 4, 12);
		ft_putchar(' ');
		if (sinfo->file_type == 6)
			write(1, sinfo->linkedfile, ft_strlen(sinfo->linkedfile));
		else
			write(1, sinfo->filename, ft_strlen(sinfo->filename));
		ft_putchar('\n');
		return ;
	}
	write(1, sinfo->filename, ft_strlen(sinfo->filename));
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
