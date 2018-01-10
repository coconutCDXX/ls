
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

void open_again(char *filename);

int		main()
{
	struct dirent	*read;
	DIR				*p;
	struct stat stats;
	struct passwd *person;
	struct group *grp;

	p = opendir("./");

	while ((read = readdir(p)) != NULL)
	{

		printf("[%s]\n", read->d_name);
		stat(read->d_name, &stats);
		person = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);

		printf("Type: ");
		printf( (S_ISBLK(stats.st_mode)) ? "Block" : (S_ISCHR(stats.st_mode)) ? "Character" :
				(S_ISDIR(stats.st_mode)) ? "Directory" : (S_ISFIFO(stats.st_mode)) ? "Pipe/Fifo" :
				(S_ISREG(stats.st_mode)) ? "File" : (S_ISLNK(stats.st_mode)) ? "Symbolic link" : "Error");
		printf("\nModes: ");
		printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
		printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
		printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
		printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
		printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
		printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
		printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
		printf( (stats.st_mode & S_IROTH) ? "r" : "-");
		printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
		printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
		printf("\nNumber of links: %hu\n", stats.st_nlink);
		printf("Owner: %s\n", person->pw_name);
		printf("Group: %s\n", grp->gr_name);
		printf("Size: %lld\n", stats.st_size);
		printf("Last modification date: %ld : %s\n", stats.st_atime, ctime(&stats.st_atime));
		if (S_ISDIR(stats.st_mode) && read->d_name[0] != '.')
			open_again(read->d_name);
	}
	closedir(p);
}

void open_again(char *filename)
{
	struct dirent	*read;
	DIR				*p;
	struct stat stats;
	struct passwd *person;
	struct group *grp;

	p = opendir(filename);
	while ((read = readdir(p)) != NULL)
	{
		char new[500];
		strcpy(new, filename);
		strcat(new, "/");
		strcat(new, read->d_name);
		printf("new [%s]\n", new);
		printf("what fails? [%s]\n", read->d_name);
		printf("--[%s]->\n", read->d_name);
		stat(new , &stats);
		person = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		printf("Type: ");
		printf( (S_ISBLK(stats.st_mode)) ? "Block" : (S_ISCHR(stats.st_mode)) ? "Character" :
				(S_ISDIR(stats.st_mode)) ? "Directory" : (S_ISFIFO(stats.st_mode)) ? "Pipe/Fifo" :
				(S_ISREG(stats.st_mode)) ? "File" : (S_ISLNK(stats.st_mode)) ? "Symbolic link" : "Error");
		printf("\nModes: ");
		printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
		printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
		printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
		printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
		printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
		printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
		printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
		printf( (stats.st_mode & S_IROTH) ? "r" : "-");
		printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
		printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
		printf("\nNumber of links: %hu\n", stats.st_nlink);
		printf("Owner: %s\n", person->pw_name);
		printf("Group: %s\n", grp->gr_name);
		printf("Size: %lld\n", stats.st_size);
		printf("Last modification date: %ld : %s\n", stats.st_atime, ctime(&stats.st_atime));
		if (S_ISDIR(stats.st_mode) && read->d_name[0] != '.')
		{
			printf("i opened once more!\n");
			//strcat(new, "/");
			printf("new [%s]\n", new);
			open_again(new);
		}
		if (S_ISREG(stats.st_mode))
			printf("just a file!\n");
	}
	closedir(p);
}