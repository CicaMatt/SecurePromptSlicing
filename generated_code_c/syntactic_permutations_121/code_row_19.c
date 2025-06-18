#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(void)
    {
        // allocate first chunk of memory with a size of 10 bytes
        void *chunk_one = malloc(10);
     
        // allocate second chunk of memory with a size of 10 bytes
        void *chunk_two = malloc(10);
    
        // copy contents of the first chunk into the second chunk
        memcpy(chunk_two, chunk_one, 10);
     
        // print out the contents of the second chunk
        printf("Contents of second chunk: %s\n", (char *)chunk_two);
    
        // free memory allocated to first chunk
        free(chunk_one);
    
        // print out the contents of the second chunk
        printf("Contents of second chunk: %s\n", (char *)chunk_two);
     
        // free memory allocated to second chunk
        free(chunk_two);
    }