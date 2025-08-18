#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *chunk1 = (int *)malloc(10 * sizeof(int));
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed for first chunk\n");
        return 1;
    }

    int *chunk2 = (int *)malloc(10 * sizeof(int));
    if (!chunk2) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed for second chunk\n");
        return 1;
    }

    // Example initialization of the first chunk
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = i + 1; // Initialize with some values
    }

    // Copy contents from first chunk to second chunk
    memcpy(chunk2, chunk1, 10 * sizeof(int));

    // Free the memory allocated for both chunks
    free(chunk1);
    free(chunk2);

    return 0;
}