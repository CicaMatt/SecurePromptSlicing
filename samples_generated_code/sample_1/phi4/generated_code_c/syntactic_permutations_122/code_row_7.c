#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory of size 10
    int *first_chunk = (int *)malloc(10 * sizeof(int));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate second chunk of memory of size 10
    int *second_chunk = (int *)malloc(10 * sizeof(int));
    if (!second_chunk) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk with some values
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = i + 1;
    }

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10 * sizeof(int));

    // Free the first chunk
    free(first_chunk);

    // Print second chunk to verify content copy
    for (int i = 0; i < 10; ++i) {
        printf("%d ", second_chunk[i]);
    }
    printf("\n");

    // Free the second chunk
    free(second_chunk);

    return 0;
}