#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    int *first_chunk = (int *)malloc(10 * sizeof(int));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate second chunk of memory
    int *second_chunk = (int *)malloc(10 * sizeof(int));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Initialize first chunk with some values
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = i + 1;
    }

    // Copy contents from the first chunk to the second chunk
    memcpy(second_chunk, first_chunk, 10 * sizeof(int));

    // Free the first chunk of memory
    free(first_chunk);

    // Print contents of the second chunk
    for (int i = 0; i < 10; ++i) {
        printf("%d ", second_chunk[i]);
    }
    printf("\n");

    // Free the second chunk of memory
    free(second_chunk);

    return 0;
}