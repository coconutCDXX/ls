#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>

int main(int ac, char **av)
{
	ssize_t buflen, vallen;
	char	*buffer, *value;

	buflen = listxattr(av[1], NULL, 0, 0);
	buffer = (char*)malloc(sizeof(char) * buflen + 1);
	listxattr(av[1], buffer, buflen, 0);
	printf("attributes: %s\n", buffer);
	vallen = getxattr(av[1], buffer, NULL, 0, 0, 0);
	value = (char*)malloc(sizeof(char) * vallen + 1);
	getxattr(av[1], buffer, value, vallen, 0, 0);
	printf("getattr: %s\n", value);
	return 0;
}
