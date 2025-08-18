#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;

    // Allocate two chunks of memory
    first_chunk = (char *)malloc(100);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    second_chunk = (char *)malloc(100);
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello, World!");

    // Copy contents of the first chunk into the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);
    printf("Memory for first chunk freed.\n");

    // Print the contents of the second chunk again after freeing the first chunk
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);
    printf("Memory for second chunk freed.\n");

    return 0;
}