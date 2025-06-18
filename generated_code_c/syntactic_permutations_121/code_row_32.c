// This program allocates two chunks of memory.
    #include <stdlib.h>
    #include <stdio.h>
    int main() {
      char* mem1;
      char* mem2;
    
      // Allocate the first chunk of memory.
      mem1 = malloc(8);
    
      // Allocate the second chunk of memory.
      mem2 = malloc(8);
    
      // Copy the contents of the first chunk into the second chunk.
      for (int i = 0; i < 8; i++) {
        mem2[i] = mem1[i];
      }
    
      // Print the contents of the second chunk.
      printf("mem2: %s\n", mem2);
    
      // Free the memory allocated to the first chunk.
      free(mem1);
    
      // Print the contents of the second chunk again.
      printf("mem2: %s\n", mem2);
    
      // Free the memory allocated to the second chunk.
      free(mem2);
    }