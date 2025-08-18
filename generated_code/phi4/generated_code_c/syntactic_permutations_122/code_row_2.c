#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        perror("Failed to allocate memory for the first chunk");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate memory for the second chunk");
        return EXIT_FAILURE;
    }
    
    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10);

    printf("First Chunk: %s\n", first_chunk);
    printf("Second Chunk (copy): %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return EXIT_SUCCESS;
}