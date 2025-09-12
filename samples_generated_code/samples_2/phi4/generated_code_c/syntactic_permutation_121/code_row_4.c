#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) return 1;

    strcpy(chunk1, "hello");

    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        free(chunk1);
        return 1;
    }

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Chunk 2: %s\n", chunk2);

    free(chunk1);

    printf("After freeing chunk 1, Chunk 2: %s\n", chunk2);

    free(chunk2);

    return 0;
}