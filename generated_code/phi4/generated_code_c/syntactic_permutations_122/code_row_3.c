#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    int *chunk1 = (int *)malloc(10 * sizeof(int));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate second chunk of memory
    int *chunk2 = (int *)malloc(10 * sizeof(int));
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Fill the first chunk with some values (e.g., 0 to 9)
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = i;
    }

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10 * sizeof(int));

    // Free the first chunk of memory
    free(chunk1);

    // Print the contents of the second chunk to verify copying
    for (int i = 0; i < 10; ++i) {
        printf("%d ", chunk2[i]);
    }
    printf("\n");

    // Free the second chunk of memory
    free(chunk2);

    return 0;
}