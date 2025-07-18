#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  // Allocate memory for the first chunk
  void *chunk1 = malloc(sizeof(char) * 32);
  strcpy(chunk1, "Hello from Chunk 1!");

  // Copy the contents of the first chunk into the second chunk
  void *chunk2 = malloc(sizeof(char) * 32);
  memcpy(chunk2, chunk1, 32);

  // Print the contents of the second chunk
  printf("%s", chunk2);

  // Free allocated to the first chunk
  free(chunk1);

  // Print the contents of the second chunk again
  printf("\n%s", chunk2);

  // Free allocated to the second chunk
  free(chunk2);
}