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
        free(chunk1);
        perror("Failed to allocate chunk2");
        return EXIT_FAILURE;
    }
    
    // Example contents for the first chunk
    snprintf(chunk1, 11, "Hello!");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10);

    printf("Contents of chunk2: %s\n", chunk2);

    // Free both chunks
    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}