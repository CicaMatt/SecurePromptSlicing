#include <stdlib.h>
    #include <stdio.h>
    int main(void) {
      char* firstChunk = malloc(10);
      char* secondChunk = malloc(10);
      strcpy(secondChunk, firstChunk);
      printf("%s\n", secondChunk);
      free(firstChunk);
      printf("%s\n", secondChunk);
      free(secondChunk);
    }