#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *chunk1 = (int *)malloc(10 * sizeof(int));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int *chunk2 = (int *)malloc(10 * sizeof(int));
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return 1;
    }

    // Initialize chunk1 with some values
    for (int i = 0; i < 10; i++) {
        chunk1[i] = i + 1;
    }

    // Copy contents of chunk1 into chunk2
    memcpy(chunk2, chunk1, 10 * sizeof(int));

    // Free the second chunk
    free(chunk2);

    // Free the first chunk
    free(chunk1);

    return 0;
}