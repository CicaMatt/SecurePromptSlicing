#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk); // Free the already allocated memory
        perror("Failed to allocate second chunk");
        return EXIT_FAILURE;
    }
    
    // Initialize first chunk with some data for demonstration
    snprintf(first_chunk, 10, "Hello");

    // Copy contents from first chunk to second chunk
    strncpy(second_chunk, first_chunk, 9);
    second_chunk[9] = '\0'; // Ensure null-termination

    printf("Second chunk: %s\n", second_chunk);

    // Free the first chunk
    free(first_chunk);

    // Free the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}