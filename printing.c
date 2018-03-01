/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:45 by cwartell          #+#    #+#             */
/*   Updated: 2018/02/28 15:26:38 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void		print_rec(t_info **sinfo, t_opt opt)
{
	t_info *tmp;

	tmp = *sinfo;
	while (tmp)
	{
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
	printf("exit loop\n");
	tmp = *sinfo;
	while (tmp && opt.R == TRUE)
	{
		if (tmp->tree != NULL)
		{
			printf("i found a LITTLE TREE! [%s]\n", tmp->tree->filename);
			print_rec(&(tmp->tree), opt);
		}
		tmp = tmp->next;
	}
}

void		write_it_all(t_info *sinfo, t_opt opt)
{
	int l;

	if (opt.l == TRUE)
	{
		//write(1, "total ", 6);
		//ft_putnbr(sinfo->dir_cont);
		//write(1, "\n", 1);
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
		//l = strlen(sinfo->filename);
		//write(1, sinfo->filename, l);
		//return;
	}
	l = strlen(sinfo->filename);
	write(1, sinfo->filename, l);
	//printf("\nwhats sinfo? [%s]", sinfo->filename);
	printf("\n--end write [%d]\n\n\n", l);
}

void		print_errors(char **av)
{
	int			x;
	int			l;
	struct stat	stats;

	x = 1;
	while (av[x])
	{
		if (stat(av[x], &stats) && av[x][0] != '-')
		{
			write(1, "ls: cannot access '", 19);
			l = strlen(av[x]);
			write(1, av[x], l);
			write(1, "': No such file or directory\n", 29);
		}
		x++;
	}
}
