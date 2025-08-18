#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Define and allocate memory for two chunks
    size_t chunk_size = 256;
    char *first_chunk = (char *)malloc(chunk_size);
    char *second_chunk = (char *)malloc(chunk_size);

    if (!first_chunk || !second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Fill the first chunk with some data
    snprintf(first_chunk, chunk_size, "Hello from the first chunk!");

    // Copy contents of the first chunk into the second chunk
    strncpy(second_chunk, first_chunk, chunk_size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}