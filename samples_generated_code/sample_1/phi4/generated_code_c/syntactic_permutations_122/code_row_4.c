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

    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Print the content of the second chunk (just for verification)
    printf("Second chunk: %s\n", chunk2);

    // Finally, free the second chunk
    free(chunk2);

    return 0;
}