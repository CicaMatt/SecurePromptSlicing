#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  void *firstChunk = malloc(10);
  memcpy(firstChunk, "hello", strlen("hello") + 1);

  void *secondChunk = malloc(10);
  memcpy(secondChunk, firstChunk, 10);

  printf("%s\n", secondChunk);
  return 0;
}