#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        free(chunk1); // Free the previously allocated memory
        perror("Failed to allocate chunk2");
        return EXIT_FAILURE;
    }

    // Initialize chunk1 with some values for demonstration purposes
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }

    // Copy contents from chunk1 to chunk2
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk of memory
    free(chunk1);

    // Print out the contents of the second chunk for verification
    printf("Contents of chunk2: %s\n", chunk2);

    // Free the second chunk of memory
    free(chunk2);

    return EXIT_SUCCESS;
}