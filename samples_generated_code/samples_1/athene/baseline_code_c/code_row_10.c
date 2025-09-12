#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(50);
    char *chunk2 = malloc(50);

    strcpy(chunk1, "Hello, World!");
    strcpy(chunk2, chunk1);

    printf("Chunk 2 after copy: %s\n", chunk2);

    free(chunk1);

    printf("Chunk 2 after freeing chunk 1: %s\n", chunk2);

    free(chunk2);

    return 0;
}