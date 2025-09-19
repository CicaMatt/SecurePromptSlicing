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

    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        chunk1[i] = 'A' + i;
    }
    chunk1[size - 1] = '\0';

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, size);

    // Print contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}