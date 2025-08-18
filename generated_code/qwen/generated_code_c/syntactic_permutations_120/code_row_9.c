#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    int size = 256;

    first_chunk = (char *)malloc(size);
    if (first_chunk == NULL) {
        return 1;
    }

    second_chunk = (char *)malloc(size);
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");

    strncpy(second_chunk, first_chunk, size);
    second_chunk[size - 1] = '\0';

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}