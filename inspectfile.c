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
	struct stat info;
	struct passwd *person;
	struct group *grp;
	//info = malloc(sizeof(struct stat));

	if (ac == 1)
	{
		perror("File Open");
		exit(EXIT_FAILURE);
	}
	stat(av[1], &info);
	person = getpwuid(info.st_uid);
	grp = getgrgid(info.st_gid);

	printf("Name: %s\n", av[1]);

	printf("Type: ");
	printf( (S_ISBLK(info.st_mode)) ? "Block" : (S_ISCHR(info.st_mode)) ? "Character" :
			(S_ISDIR(info.st_mode)) ? "Directory" : (S_ISFIFO(info.st_mode)) ? "Pipe/Fifo" :
			(S_ISREG(info.st_mode)) ? "File" : (S_ISLNK(info.st_mode)) ? "Symbolic link" : "Error");
	printf("\nModes: ");
	printf( (S_ISDIR(info.st_mode)) ? "d" : "-");
	printf( (info.st_mode & S_IRUSR) ? "r" : "-");
	printf( (info.st_mode & S_IWUSR) ? "w" : "-");
	printf( (info.st_mode & S_IXUSR) ? "x" : "-");
	printf( (info.st_mode & S_IRGRP) ? "r" : "-");
	printf( (info.st_mode & S_IWGRP) ? "w" : "-");
	printf( (info.st_mode & S_IXGRP) ? "x" : "-");
	printf( (info.st_mode & S_IROTH) ? "r" : "-");
	printf( (info.st_mode & S_IWOTH) ? "w" : "-");
	printf( (info.st_mode & S_IXOTH) ? "x" : "-");
	printf("\nNumber of links: %hu\n", info.st_nlink);
	printf("Owner: %s\n", person->pw_name);
	printf("Group: %s\n", grp->gr_name);
	printf("Size: %lld\n", info.st_size);
	printf("Last modification date: %ld : %s\n", info.st_atime, ctime(&info.st_atime));
}
