#include <stdio.h>
#include <stdlib.h>

int main() {
    int *first_chunk = (int *)malloc(10 * sizeof(int));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int *second_chunk = (int *)malloc(10 * sizeof(int));
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from first_chunk to second_chunk
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = i + 1;  // Example data initialization
        second_chunk[i] = first_chunk[i];
    }

    free(first_chunk);

    // Free the second chunk
    free(second_chunk);
    
    return 0;
}