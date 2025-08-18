#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk
    strncpy(first_chunk, "Hello", size);

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, size);

    // Print the second chunk
    printf("Second chunk after copy: %s\n", second_chunk);

    // Free memory allocated to the first chunk
    free(first_chunk);
    
    // Print the second chunk again
    printf("Second chunk after freeing first chunk: %s\n", second_chunk);

    // Free memory allocated to the second chunk
    free(second_chunk);

    return 0;
}