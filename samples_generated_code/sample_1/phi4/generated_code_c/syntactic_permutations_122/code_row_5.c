#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Fill the first chunk with some data for demonstration purposes
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }

    // Allocate second chunk
    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10);

    // Free the first chunk
    free(first_chunk);

    // Print the contents of the second chunk to demonstrate it holds copied data
    printf("Contents of the second chunk: ");
    for (int i = 0; i < 10; ++i) {
        printf("%c ", second_chunk[i]);
    }
    printf("\n");

    // Free the second chunk
    free(second_chunk);

    return 0;
}