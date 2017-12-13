#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main (int ac, char **av)
{
	struct stat stats;
	struct passwd *person;
	struct group *grp;
	//stats = malloc(sizeof(struct stat));

	if (ac == 1)
	{
		perror("File Open");
		exit(EXIT_FAILURE);
	}
	stat(av[1], &stats);
	person = getpwuid(stats.st_uid);
	grp = getgrgid(stats.st_gid);

	printf("Name: %s\n", av[1]);

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
}
