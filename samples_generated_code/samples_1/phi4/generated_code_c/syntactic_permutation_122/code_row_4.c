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
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Print contents of the second chunk (to verify copy)
    printf("Contents of the second chunk: ");
    for (int i = 0; i < 10; ++i) {
        putchar(chunk2[i]);
    }
    putchar('\n');

    // Free the second chunk
    free(chunk2);

    return 0;
}