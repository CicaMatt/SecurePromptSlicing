#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = malloc(20);
    char *second_chunk = malloc(20);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");

    strcpy(second_chunk, first_chunk);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}