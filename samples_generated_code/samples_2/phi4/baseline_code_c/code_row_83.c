#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int size = 10;
    
    char *first_chunk = malloc(size);
    if (first_chunk == NULL) {
        perror("Failed to allocate memory for first chunk");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk
    for (int i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0';

    char *second_chunk = malloc(size);
    if (second_chunk == NULL) {
        perror("Failed to allocate memory for second chunk");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy the contents of the first chunk into the second
    memcpy(second_chunk, first_chunk, size);

    printf("Contents of the second chunk after copy: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    printf("Contents of the second chunk after freeing the first chunk: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}