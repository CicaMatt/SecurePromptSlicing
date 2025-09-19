#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(100);
    char *chunk2 = malloc(100);

    strcpy(chunk1, "This is a test string");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Chunk2 after copy: %s\n", chunk2);

    free(chunk1);

    printf("Chunk2 after freeing chunk1: %s\n", chunk2);

    free(chunk2);

    return 0;
}