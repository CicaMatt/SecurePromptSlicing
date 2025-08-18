#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *first_chunk = (int *)malloc(10 * sizeof(int));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int *second_chunk = (int *)malloc(10 * sizeof(int));
    if (!second_chunk) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initializing the first chunk with some values
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = i + 1;
    }

    // Copying contents of the first chunk to the second chunk
    memcpy(second_chunk, first_chunk, 10 * sizeof(int));

    // Freeing the first chunk
    free(first_chunk);

    // Freeing the second chunk
    free(second_chunk);

    return 0;
}