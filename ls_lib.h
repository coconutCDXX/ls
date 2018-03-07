/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:07:14 by cwartell          #+#    #+#             */
/*   Updated: 2018/03/07 03:17:43 by coralie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LIB_H
# define LS_LIB_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <dirent.h>

typedef enum		bools
{
	FALSE,
	TRUE
}					boolean;

typedef struct		s_opt
{
	boolean		a;
	boolean		l;
	boolean		R;
	boolean		r;
	boolean		t;
}					t_opt;

typedef struct		s_info
{
	int				dir_cont;
	char			*str_rights;
	int				file_type;
	char			*user_name;
	char			*grp_name;
	int				bytes;
	time_t			time_sort;
	char			*date;
	char			*filename;
	char			*linkedfile;
	struct s_info	*next;
	struct s_info	*tree;
}					t_info;

void				verify_options(char **av, char *ret);
int					valid_options(char o, char *cmp_options);
void				read_options(int ac, char **av, char *options);
void				sort_command(t_info *sinfo, t_opt opt);
void				print_rec(t_info **sinfo, t_opt opt);
void				write_it_all(t_info *sinfo, t_opt opt);
void				print_errors(char **av);
void				sort_by_r(t_info **sinfo, t_opt opt);
void				sort_by_time(t_info **sinfo, t_opt opt);
void				sort_by_alpha(t_info **sinfo);
void				save_data1(t_info *sinfo, char *filename);
void				save_data2(t_info *sinfo, char *filename, int nf, int tf);
void				set_data(t_info *sinfo, char *treename, char *name);
void				set_lstat(t_info *sinfo, char *treename, char *name);
void				set_time(t_info *sinfo, struct stat stats);
void				set_types_name(t_info *sinfo, char *filename, char *dname, struct stat stats);
void				set_rights(t_info *sinfo, struct stat stats);
void				set_rights_usr_grp(t_info *sinfo, struct stat stats);
void				set_rights_oth(t_info *sinfo, struct stat stats);
void				set_uid_gid_size(t_info *sinfo, struct stat stats);
int					count_dir(char *filename);
void				ft_putnbr(int n);
void				ft_putchar(char c);
char				*create_treename(char *read, char *filename);
t_opt				set_options_zero(t_opt struct_opt, char *options);
int					check_alpha(char *a, char *b);
int					check_alpha_bis(char x, char y);
char				**spec_file(int ac, char **av, t_opt opt, t_info *sinfo);
void				end_specific_file(t_info *sinfo, t_opt opt, char **av);
int					check_av(char **av, int ac);
char				**folders_av(int ac, char **av, int *nf, t_opt opt);
void				sort_folders(char **f, t_opt opt);
char				**sort_rev_folders(char **f);
void				sort_time_folders(char **f);
time_t				check_time(char *t);
void				save_folders(char **f, t_opt opt);

#endif
