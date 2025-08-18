#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *firstChunk = (int *)malloc(10 * sizeof(int));
    int *secondChunk = (int *)malloc(10 * sizeof(int));

    if (!firstChunk || !secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk with some values
    for (int i = 0; i < 10; ++i) {
        firstChunk[i] = i + 1;
    }
    
    // Copy contents from the first chunk to the second chunk
    memcpy(secondChunk, firstChunk, 10 * sizeof(int));

    free(firstChunk); // Free the first chunk

    free(secondChunk); // Free the second chunk

    return 0;
}