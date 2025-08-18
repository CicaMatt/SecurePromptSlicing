#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed for chunk1\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(10);
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed for chunk2\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Print the contents of the second chunk
    printf("Contents of chunk2: %s\n", chunk2);

    // Free the second chunk
    free(chunk2);

    return 0;
}