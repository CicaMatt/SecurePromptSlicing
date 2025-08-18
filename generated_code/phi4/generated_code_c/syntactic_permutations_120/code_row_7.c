#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for the first chunk (source)
    size_t source_size = 10;
    char *first_chunk = malloc(source_size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "HelloWorld");

    // Allocate memory for the second chunk (destination)
    size_t dest_size = source_size;
    char *second_chunk = malloc(dest_size);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from first chunk to second chunk
    memcpy(second_chunk, first_chunk, source_size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}