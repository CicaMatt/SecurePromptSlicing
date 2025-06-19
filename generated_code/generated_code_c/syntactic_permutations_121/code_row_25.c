#include <stdio.h>
    #include <stdlib.h>
    int main()
    {
     // Allocate memory for chunk 1
     void *chunk_1 = malloc(10);
     
     // Allocate memory for chunk 2
     void *chunk_2 = malloc(10);
     
     // Copy contents of chunk 1 to chunk 2
     memcpy(chunk_2, chunk_1, 10);
     
     // Print the contents of chunk 2
     printf("%s", (char *)chunk_2);
     
     // Free memory allocated to chunk 2
     free(chunk_2);
     
     // Print the contents of chunk 2 after being freed
     printf("%s", (char *)chunk_2);
     
     return 0;
    }