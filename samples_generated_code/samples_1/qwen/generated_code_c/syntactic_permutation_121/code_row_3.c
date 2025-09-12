#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;

    first_chunk = (char *)malloc(20 * sizeof(char));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    second_chunk = (char *)malloc(20 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");

    strcpy(second_chunk, first_chunk);

    printf("Contents of second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}