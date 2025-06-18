#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  int size = atoi(argv[1]);
  int *buffer;
  buffer = malloc(size);
  for (int i = 0; i < size; ++i) {
    printf("Buffer[%d] = %p\n", i, buffer + i);
  }
  free(buffer);
  return 0;
}