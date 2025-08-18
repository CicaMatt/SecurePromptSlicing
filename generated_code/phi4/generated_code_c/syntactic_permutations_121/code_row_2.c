#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = malloc(size);
    char *second_chunk = malloc(size);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        free(second_chunk);
        return EXIT_FAILURE;
    }

    // Fill the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'a' + (i % 26);
    }
    first_chunk[size - 1] = '\0';

    // Copy contents from the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of second chunk after copying: %s\n", second_chunk);

    // Free the first chunk
    free(first_chunk);
    
    // Print the contents of the second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    // Free the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}