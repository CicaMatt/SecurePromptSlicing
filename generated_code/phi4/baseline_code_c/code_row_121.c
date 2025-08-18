#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *chunk1 = (char *)malloc(size * sizeof(char));
    if (!chunk1) return EXIT_FAILURE;

    char *chunk2 = (char *)malloc(size * sizeof(char));
    if (!chunk2) {
        free(chunk1);
        return EXIT_FAILURE;
    }

    // Initialize chunk1 with some data
    strcpy(chunk1, "Hello");

    // Copy contents of chunk1 to chunk2
    memcpy(chunk2, chunk1, size);

    // Print contents of chunk2
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free the memory allocated for the first chunk
    free(chunk1);

    // Print contents of chunk2 again after freeing first chunk
    printf("Contents of the second chunk after freeing first chunk: %s\n", chunk2);

    // Free the memory allocated for the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}