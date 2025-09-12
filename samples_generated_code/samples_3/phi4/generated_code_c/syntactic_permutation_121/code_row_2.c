#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10;
    size_t size2 = 15;

    char *chunk1 = (char *)malloc(size1);
    if (!chunk1) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size2);
    if (!chunk2) {
        free(chunk1);
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }

    // Fill the first chunk with some data
    for (size_t i = 0; i < size1 - 1; ++i) {
        chunk1[i] = 'A' + (i % 26);
    }
    chunk1[size1 - 1] = '\0';

    // Copy contents of the first chunk into the second
    memcpy(chunk2, chunk1, size1);

    // Print the contents of the first chunk
    printf("Contents of the first chunk: %s\n", chunk1);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print the contents of the second chunk
    printf("Contents of the second chunk (after copying): %.*s\n", size1 - 1, chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}