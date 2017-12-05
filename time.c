#include <time.h>
#include <stdio.h>

int main()
{
	time_t currentime;
	time(&currentime);

	printf("Current time: %s", ctime(&currentime));
	return 0;
}
