#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = malloc(10);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *second_chunk = malloc(10);
    if (second_chunk == NULL) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "abcdefghij");

    // Copy contents from the first chunk to the second chunk
    memcpy(second_chunk, first_chunk, 10);

    printf("First chunk: %s\n", first_chunk);
    printf("Second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}