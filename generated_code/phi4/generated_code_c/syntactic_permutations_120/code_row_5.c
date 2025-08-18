#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Define the size for both chunks

    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(size * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize contents of the first chunk
    strcpy(first_chunk, "Hello");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(size * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy contents from first to second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}