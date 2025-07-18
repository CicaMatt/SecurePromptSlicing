#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int size = atoi(argv[1]);
  char *buffer = malloc(size);
  memset(buffer, '\0', size);
  printf("%s", buffer);
  free(buffer);
}
