#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *s;
	char noheap[] = "hicora!";
	s = (char*)malloc(sizeof(char) * 15);

	strcpy(s, noheap);
	printf("[%s]\n", s);
	//free(s);
	return 0;
}