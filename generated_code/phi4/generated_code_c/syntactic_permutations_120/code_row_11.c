#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory and initialize it with some data
    size_t first_chunk_size = 10;
    char *first_chunk = (char *)malloc(first_chunk_size);
    
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Fill the first chunk with example data
    strncpy(first_chunk, "HelloWorld", first_chunk_size);
    
    // Allocate second chunk of memory, same size as first chunk
    char *second_chunk = (char *)malloc(first_chunk_size);
    
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }
    
    // Copy contents from the first chunk to the second chunk
    memcpy(second_chunk, first_chunk, first_chunk_size);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);
    
    // Free allocated memory
    free(first_chunk);
    free(second_chunk);
    
    return 0;
}