/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:36:27 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/05 02:09:20 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls_lib.h>

void	delete_me(t_info *sinfo)
{
	t_info *next;

	while (sinfo != NULL)
	{
		if (sinfo->str_rights)
			free(sinfo->str_rights);
		if (sinfo->user_name)
			free(sinfo->user_name);
		if (sinfo->grp_name)
			free(sinfo->grp_name);
		if (sinfo->date)
			free(sinfo->date);
		if (sinfo->filename)
			free(sinfo->filename);
		if (sinfo->file_type == 6)
			free(sinfo->linkedfile);
		if (sinfo->filepath)
			free(sinfo->filepath);
		if (sinfo->tree)
			delete_me(sinfo->tree);
		next = sinfo;
		sinfo = sinfo->next;
		free(next);
	}
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