#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(100);
    char *chunk2 = malloc(100);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    strcpy(chunk1, "This is some sample text to copy.");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Chunk1: %s\n", chunk1);
    free(chunk1);

    printf("Chunk2: %s\n", chunk2);
    free(chunk2);

    return 0;
}