#include <stdio.h>
#include <stdlib.h>

int main() {
  char *buf;
  buf = malloc(1024); // allocate 1kb buffer
  free(buf);          // release the memory

  return 0;
}