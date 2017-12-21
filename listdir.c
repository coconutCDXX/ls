#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int ac, char **av)
{
	DIR *p;
	struct dirent *read;
	int a;

	p = opendir("./");
	if (p == NULL)
	{
		printf("Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while ((read = readdir(p)) != NULL)
	{
		printf("filename: %s\n", read->d_name);
	}
	ret("prout");
	closedir(p);
}
