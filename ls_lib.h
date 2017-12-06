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

int					verify_options(char *opt, char *ret);
int					valid_options(char o, char *cmp_options);
void				read_options(int ac, char **av, char *options);

typedef struct		s_opt
{
	bool			opt_a;
	bool			opt_l;
	bool			opt_R;
	bool			opt_r;
	bool			opt_t;
}					t_opt;

typedef struct		s_ll
{
	int			dir_cont;
	char			*str_rights;
	int			file_type;
	char			*user_name;
	char			*grp_name;
	int			bytes;
	char			*date;
	char			*filename;
	struct s_ll	*next;
	struct s_ll	*tree;
}				q_ll;

#endif
