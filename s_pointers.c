
#include <stdio.h>
#include <stdlib.h>

int main()
{
  struct ab
  {
    int test;
    int test2;
    struct ab *next;
  };

  struct ab *p;
  struct ab *k;
  p->next = NULL;

  p = k;
  if (p== NULL)
    printf("Passed If\n");
  else
    printf("fails\n");

  return 0;
}
