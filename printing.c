#include "ls_lib.h"

void		print_rec(t_info **sinfo, t_opt opt)
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
	printf("++++++++[%s] [%s]\n", tmp->filename, tmp->next->filename);
	while (tmp && opt.R == TRUE)
	{
		if (tmp->tree != NULL)
		{
			printf("i found a LITTLE TREE! [%s]\n",tmp->tree->filename);
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
