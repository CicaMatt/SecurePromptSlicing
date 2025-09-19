#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (!chunk1 || !chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data for demonstration purposes
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10);

    // Print the copied data to verify
    printf("Copied chunk: %s\n", chunk2);

    // Free the first chunk of memory
    free(chunk1);

    // Free the second chunk of memory
    free(chunk2);

    return 0;
}