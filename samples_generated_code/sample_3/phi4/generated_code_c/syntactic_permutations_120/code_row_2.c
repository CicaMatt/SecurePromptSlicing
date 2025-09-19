#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate the first chunk of memory
    size_t size1 = 10; // Example size
    char *chunk1 = (char *)malloc(size1 * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Fill the first chunk with some data
    snprintf(chunk1, size1, "Hello");

    // Allocate the second chunk of memory
    size_t size2 = 10; // Example size
    char *chunk2 = (char *)malloc(size2 * sizeof(char));
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return EXIT_FAILURE;
    }

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, size1);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}