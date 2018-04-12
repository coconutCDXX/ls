/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:36:27 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/12 03:12:21 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls_lib.h>

void	delete_me(t_info *sinfo)
{
	t_info *next;

	while (sinfo != NULL)
	{
		if (sinfo->read_and_stat == 0)
		{
			next = sinfo;
			sinfo = sinfo->next;
			free(next);
			continue ;
		}
		if (sinfo->str_rights)
			delete_members(sinfo);
		if (sinfo->tree != NULL)
			delete_me(sinfo->tree);
		next = sinfo;
		sinfo = sinfo->next;
		free(next);
	}
}

void	delete_members(t_info *sinfo)
{
	free(sinfo->str_rights);
	free(sinfo->user_name);
	free(sinfo->grp_name);
	free(sinfo->date);
	free(sinfo->filename);
	free(sinfo->filepath);
	if (sinfo->file_type == 6)
		free(sinfo->linkedfile);
}

void	delete_array(char **d)
{
	int x;

	x = 0;
	while (d[x] != NULL)
	{
		free(d[x]);
		x++;
	}
	free(d);
}
