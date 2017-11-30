#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

int main(int ac, char **av)
{
	DIR *p;
	struct dirent *read;

	p = opendir(av[1]);
	if (p == NULL)
	{
		printf("Error!\n");
		return 0;
	}
	while ((read = readdir(p)) != NULL)
	{
		printf("filename: %s\n", read->d_name);
	}
	closedir(p);
}
