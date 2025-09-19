#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *chunk1 = (char *)malloc(size);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk
    for (size_t i = 0; i < size - 1; ++i) {
        chunk1[i] = 'a' + i;
    }
    chunk1[size - 1] = '\0';

    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return 1;
    }

    // Copy contents of first chunk to second chunk
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("Contents of chunk2 after copying: %s\n", chunk2);

    // Free memory allocated to the first chunk
    free(chunk1);

    // Print the contents of the second chunk again
    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    // Free memory allocated to the second chunk
    free(chunk2);

    return 0;
}