#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    int *first_chunk = (int *)malloc(10 * sizeof(int));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate second chunk of memory
    int *second_chunk = (int *)malloc(10 * sizeof(int));
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Initialize first chunk with some values
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = i + 1;
    }

    // Copy contents of the first chunk to second chunk
    memcpy(second_chunk, first_chunk, 10 * sizeof(int));

    // Free the first chunk
    free(first_chunk);

    // Free the second chunk
    free(second_chunk);

    return 0;
}