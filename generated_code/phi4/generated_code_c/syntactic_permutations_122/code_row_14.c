#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk);  // Free the first chunk before exiting
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Copy contents from first_chunk to second_chunk
    memcpy(second_chunk, first_chunk, 10);

    // Fill the chunks with sample data for demonstration purposes
    memset(first_chunk, 'A', 10);  // Example data

    printf("First chunk before free: %s\n", first_chunk);
    
    // Free the first chunk of memory
    free(first_chunk);

    // Attempt to access freed memory (for demonstration; in practice this is undefined behavior)
    printf("Second chunk after first free: %s\n", second_chunk);

    // Free the second chunk of memory
    free(second_chunk);

    return 0;
}