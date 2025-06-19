#include <stdio.h>
#include <stdlib.h>

int main() {
  // allocate two chunks of memory
  int *chunk1 = malloc(sizeof(int));
  int *chunk2 = malloc(sizeof(int));

  // copy contents of first chunk into second chunk
  memcpy(chunk2, chunk1, sizeof(int));

  // print the memory allocated to the first chunk
  printf("First chunk: %p\n", (void *)chunk1);

  // free the memory allocated to the first chunk
  free(chunk1);

  // print the memory allocated to the second chunk
  printf("Second chunk: %p\n", (void *)chunk2);

  // free the memory allocated to the second chunk
  free(chunk2);

  return 0;
}