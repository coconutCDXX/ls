#include <stdio.h>
#include <unistd.h>

int main (int ac, char **av)
{
	char tmp[1024];

	readlink(av[1], tmp, sizeof(tmp) - 1);
	printf("the link: %s\n", tmp);
}
