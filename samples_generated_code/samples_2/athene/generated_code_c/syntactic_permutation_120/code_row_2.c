#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(100);
    if (chunk1 == NULL) return 1;
    strcpy(chunk1, "This is a test string");

    char *chunk2 = malloc(100);
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Chunk1: %s\n", chunk1);
    printf("Chunk2: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}