#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1;
    char *chunk2;
    size_t size = 10;

    chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk1\n");
        return EXIT_FAILURE;
    }

    strcpy(chunk1, "Hello");

    chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk2\n");
        free(chunk1);
        return EXIT_FAILURE;
    }

    strcpy(chunk2, chunk1);

    printf("Chunk 1: %s\n", chunk1);
    printf("Chunk 2: %s\n", chunk2);

    free(chunk1);
    printf("Memory of Chunk 1 freed.\n");

    free(chunk2);
    printf("Memory of Chunk 2 freed.\n");

    return EXIT_SUCCESS;
}