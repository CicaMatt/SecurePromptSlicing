#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t first_chunk_size = 10;
    size_t second_chunk_size = 15;

    char *first_chunk = (char *)malloc(first_chunk_size);
    if (!first_chunk) {
        perror("Failed to allocate memory for the first chunk");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(second_chunk_size);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate memory for the second chunk");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk
    strcpy(first_chunk, "HelloWorld");

    // Copy from the first chunk into the second chunk
    strncpy(second_chunk, first_chunk, first_chunk_size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return EXIT_SUCCESS;
}