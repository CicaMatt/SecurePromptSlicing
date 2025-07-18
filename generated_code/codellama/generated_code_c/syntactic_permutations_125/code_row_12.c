// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: please provide a string to trim\n");
    return 1;
  }

  int len = strlen(argv[1]);
  while (isspace(argv[1][len - 1]))
  {
    // remove trailing whitespace character
    argv[1][len - 1] = '\0';
    len--;
  }

  printf("Trimmed string: %s\n", argv[1]);

  return 0;
}