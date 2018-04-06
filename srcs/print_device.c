/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 06:27:50 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/06 08:02:18 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_lib.h"

void		write_major_minor(t_info *sinfo)
{
	ft_putnbr(sinfo->bytes);
	if (sinfo->device)
	{
		write(1, ",", 1);
		ft_putnbr(sinfo->minor);
	}
}

void		write_pretty_colors(t_info *sinfo)
{
	if (sinfo->file_type == 6)
	{
		write(1, PURPLE, 11);
		write(1, sinfo->linkedfile, ft_strlen(sinfo->filename));
		write(1, FLUSH, 4);
		write(1, sinfo->linkedfile + ft_strlen(sinfo->filename),
		ft_strlen(sinfo->linkedfile) - ft_strlen(sinfo->filename));
	}
	else if (sinfo->str_rights[0] == 'd')
	{
		write(1, CYAN, 10);
		write(1, sinfo->filename, ft_strlen(sinfo->filename));
	}
	else if (sinfo->str_rights[0] == 'c')
	{
		write(1, BLUE_YELLOW, 15);
		write(1, sinfo->filename, ft_strlen(sinfo->filename));
	}
	else
		more_pretty_colors(sinfo);
	write(1, FLUSH, 4);
}

void		more_pretty_colors(t_info *sinfo)
{
	if (sinfo->str_rights[0] == 'p')
	{
		write(1, YELLOW, 11);
		write(1, sinfo->filename, ft_strlen(sinfo->filename));
	}
	else if (sinfo->str_rights[0] == 'b')
	{
		write(1, BLUE_CYAN, 14);
		write(1, sinfo->filename, ft_strlen(sinfo->filename));
	}
	else
	{
		write(1, FLUSH, 4);
		write(1, sinfo->filename, ft_strlen(sinfo->filename));
	}
}
