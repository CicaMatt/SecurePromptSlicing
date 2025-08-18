#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Size of each chunk

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        free(chunk1); // Free the first chunk before exiting
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }

    // Initialize the contents of the first chunk
    strcpy(chunk1, "Hello");

    // Copy the contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}