#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **change_av(char **av);

int main(int ac, char **av)
{
	// time_t currentime;
	// time(&currentime);
	//
	// printf("Current time: %s", ctime(&currentime));
	// return 0;

	av = change_av(av);
	printf("[%s] [%s] [%s]\n", av[0], av[1], av[2]);
	return 0;
}
char **change_av(char **av)
{
	//char f[3][3] = {"abc", "def", "hij"};
	char **f;
	f = malloc(sizeof(char*) * 3);
	f[0] = malloc(sizeof(char) * 3);
	f[1] = malloc(sizeof(char) * 3);
	f[2] = malloc(sizeof(char) * 3);
	strcpy(f[0], "abc");
	strcpy(f[1], "lol");
	strcpy(f[2], "eee");

	return (f);
}
