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

typedef enum		bools{FALSE, TRUE} boolean;

typedef struct		s_opt
{
	boolean		opt_a;
	boolean		opt_l;
	boolean		opt_R;
	boolean		opt_r;
	boolean		opt_t;
}				t_opt;

typedef struct		s_info
{
	int			dir_cont;
	char			*str_rights;
	int			file_type;
	char			*user_name;
	char			*grp_name;
	int			bytes;
	time_t		time_sort;
	char			*date;
	char			*filename;
	struct s_info	*next;
	struct s_info	*tree;
}				t_info;

int				verify_options(char **av, char *ret);
int				valid_options(char o, char *cmp_options);
void				read_options(int ac, char **av, char *options);
void				sort_command(t_info *sinfo, t_opt opt, char **av);
void				print_rec(t_info **sinfo, t_opt opt, char **av);
void				write_it_all(t_info *sinfo, t_opt opt);
void				sort_by_r(t_info **sinfo, t_opt opt);
void				sort_by_time_xor_rev(t_info **sinfo, t_opt opt);
void				sort_by_alpha(t_info **sinfo);
void				save_data1(t_info *sinfo, char *filename);
//void				save_data2(t_info *sinfo, char *filename);
void				set_time(t_info *sinfo, char *filename);
void				set_types_name(t_info *sinfo, char *filename, char *dname);
void				set_rights(t_info *sinfo, char *filename);
void				set_rights_USR_GRP(t_info *sinfo, struct stat);
void				set_rights_OTH(t_info *sinfo, struct stat);
void				set_uid_gid_size(t_info *sinfo, char *filename);
int					count_dir(void);
void				ft_putnbr(int n);
void				ft_putchar(char c);
char				*create_treename(char *read, char *filename);
t_opt			set_options_zero(struct s_opt);
int				check_alpha(char *a, char *b);
void quick_memtest(t_info *sinfo);

#endif
