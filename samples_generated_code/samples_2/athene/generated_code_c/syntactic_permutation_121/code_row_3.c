#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(100);
    char *chunk2 = malloc(100);

    strcpy(chunk1, "This is a test string");

    strcpy(chunk2, chunk1);

    printf("Chunk 1: %s\n", chunk1);
    free(chunk1);

    printf("Chunk 2: %s\n", chunk2);
    free(chunk2);

    return 0;
}