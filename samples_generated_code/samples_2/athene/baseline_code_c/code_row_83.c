#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(20);
    char *chunk2 = malloc(20);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    strcpy(chunk1, "Hello, World!");
    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Chunk2: %s\n", chunk2);
    free(chunk1);

    printf("Chunk2 after freeing chunk1: %s\n", chunk2);
    free(chunk2);

    return 0;
}