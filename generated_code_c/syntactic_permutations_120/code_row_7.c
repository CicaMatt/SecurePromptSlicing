#include <stdlib.h>
    #include <stdio.h>
    
    int main(){
      char *chunk1 = "This is chunk 1.";
      size_t chunk_size = strlen(chunk1) + 1;
      char *chunk2 = malloc(chunk_size);
      memcpy(chunk2, chunk1, chunk_size);
      printf("%s\n", chunk2);
      return 0;
    }