#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    int size = 10;

    first_chunk = (char *)malloc(size * sizeof(char));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed for first chunk\n");
        return 1;
    }

    second_chunk = (char *)malloc(size * sizeof(char));
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed for second chunk\n");
        free(first_chunk);
        return 1;
    }

    strcpy(first_chunk, "HelloWorld");

    memcpy(second_chunk, first_chunk, size);

    printf("Contents of the second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}