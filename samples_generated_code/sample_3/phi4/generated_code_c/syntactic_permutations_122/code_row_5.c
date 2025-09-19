#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(10);
    if (chunk2 == NULL) {
        free(chunk1); // Free the first chunk before exiting
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize chunk1 with some data
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i; // Fill with characters A to J
    }

    // Copy contents of chunk1 into chunk2
    memcpy(chunk2, chunk1, 10);

    // Print the copied data
    printf("Contents of second chunk: %s\n", chunk2);

    // Free the first chunk
    free(chunk1);
    
    // Free the second chunk
    free(chunk2);

    return 0;
}