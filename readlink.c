#include <stdio.h>
#include <unistd.h>
# include <sys/stat.h>

int main (int ac, char **av)
{
// 	char tmp[1024];
//
// 	readlink(av[1], tmp, sizeof(tmp) - 1);
// 	printf("the link: %s\n", tmp);
	int x;
	struct stat stats;
	x = stat(av[1], &stats);
	if (x == -1)
		perror("eroero!");
	return 0;
}
