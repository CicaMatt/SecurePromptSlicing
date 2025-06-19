#include <stdio.h>
#include <stdlib.h>
int main()
{
  char str[1024];
  sprintf(str, "ls -ltr %s", argv[1]);
  system(str);
  return 0;
}