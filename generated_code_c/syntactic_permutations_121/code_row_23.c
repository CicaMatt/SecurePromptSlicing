#include <stdio.h>
#include <string.h>
int main(void)
{
  char *p = malloc(10);
  char *q = malloc(5);
  memcpy(q, p, 5);
  printf("%s", q);
  free(p);
  printf("%s", q);
  free(q);
  return 0;
}