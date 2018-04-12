/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwartell <cwartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 16:07:14 by cwartell          #+#    #+#             */
/*   Updated: 2018/04/12 04:31:29 by cwartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LIB_H
# define LS_LIB_H
# define CYAN "\e[38;5;33m"
# define BLUE_CYAN "\e[34;48;5;33m"
# define BLUE_YELLOW "\e[34;48;5;221m"
# define YELLOW "\e[38;5;226m"
# define PURPLE "\e[38;5;129m"
# define FLUSH "\e[0m"

# include "libft.h"
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

typedef enum		e_bools
{
	FALSE,
	TRUE
}					t_boolean;

typedef struct		s_opt
{
	t_boolean		a;
	t_boolean		l;
	t_boolean		cr;
	t_boolean		r;
	t_boolean		t;
}					t_opt;

typedef struct		s_info
{
	int				block_cont;
	int				dir_cont;
	int				read_and_stat;
	int				p_dir_cont;
	char			*str_rights;
	int				file_type;
	char			*user_name;
	char			*grp_name;
	int				bytes;
	int				minor;
	t_boolean		device;
	time_t			time_sort;
	char			*date;
	char			*filename;
	char			*linkedfile;
	char			*filepath;
	struct s_info	*next;
	struct s_info	*tree;
}					t_info;

void				verify_options(char **av, char *ret);
int					valid_options(char o, char *cmp_options);
void				save_command(int ac, char **av, char *options);
int					check_av(char **av, int ac);

void				save_data1(t_info *sinfo, char *filename, t_boolean b);
void				save_folders(char **f, t_opt opt);
char				**folders_av(int ac, char **av, t_opt opt);
int					count_dir(char *filename, char a);
char				*create_treename(char *read, char *filename);

void				save_data2(t_info *sinfo, char *filename, int nf, int tf);
int					spec_file(int ac, char **av, t_opt opt, t_info *sinfo);
int					files_count(char **av);
void				end_specific_file(t_info *sinfo, t_opt opt, char **av);
void				valid_file(char **av, int *x, int *ac);

void				sort_command(t_info *sinfo, t_opt opt, t_boolean b);
void				sort_by_r(t_info **sinfo);
void				sort_recursive(t_info *sinfo, t_opt opt);
void				check_permissions(t_info *sinfo);
int					read_and_stat(t_info *sinfo, char *treename);

void				sort_by_alpha(t_info **sinfo);
int					check_alpha(char *a, char *b);
int					check_alpha_bis(char x, char y);

void				sort_folders(char **f, t_opt opt);
void				sort_rev_folders(char **f);
void				sort_time_folders(char **f);
void				sort_by_time(t_info **sinfo);
time_t				check_time(char *t);

int					save_data2_lstat(t_info *sinfo, char *fn, int nf);
void				set_data(t_info *sinfo, char *treename, char *name,
					t_boolean b);
void				set_lstat(t_info *sinfo, char *treename, char *name,
					t_boolean b);
void				set_data_tree(t_info *sinfo, char *name, char *treename,
					t_boolean b);
void				set_types_name(t_info *sinfo, char *fp, char *dname,
					struct stat stats);

void				set_rights_time(t_info *sinfo, struct stat stats);
void				set_rights_usr_grp(t_info *sinfo, struct stat stats);
void				set_rights_oth(t_info *sinfo, struct stat stats);
void				set_uid_gid_size_links(t_info *sinfo, struct stat stats);
t_opt				set_options_zero(char *options);

void				print_rec(t_info **sinfo, t_opt opt, t_boolean b);
void				print_blocks(t_info *sinfo, t_opt opt);
void				print_errors(char **av);
void				print_error_perm(char *filename);
void				print_tree(t_info *tmp, t_opt opt);

void				write_it_all(t_info *sinfo, t_opt opt);
void				write_major_minor(t_info *sinfo);
void				write_pretty_colors(t_info *sinfo);
void				more_pretty_colors(t_info *sinfo);

void				delete_me(t_info *sinfo);
void				delete_array(char **d);
void				delete_members(t_info *sinfo);

#endif
