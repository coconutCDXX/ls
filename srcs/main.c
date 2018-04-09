/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:35:31 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/08 22:38:08 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls_lib.h>

int		main(int ac, char **av)
{
	char	options[6];

	verify_options(av, options);
	save_command(ac, av, options);
	return (0);
}

void	save_command(int ac, char **av, char *options)
{
	t_opt	opt;
	t_info	*sinfo;
	char	**folders;
	int		fileck;

	fileck = 0;
	sinfo = (t_info*)malloc(sizeof(t_info));
	opt = set_options_zero(options);
	if (check_av(av, ac))
	{
		folders = folders_av(ac, av, opt);
		fileck = spec_file(ac, av, opt, sinfo);
		if (folders[0] != NULL)
		{
			if (fileck == 1)
				write(1, "\n", 1);
			save_folders(folders, opt);
			delete_array(folders);
		}
		exit(1);
	}
	save_data1(sinfo, "./", opt.cr);
	if (sinfo->filename)
		sort_command(sinfo, opt, TRUE);
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

int		check_av(char **av, int ac)
{
	int		x;

	x = 1;
	while (ac > 1)
	{
		if (av[x][0] != '-')
			return (1);
		x++;
		ac--;
	}
	return (0);
}
