#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1, *chunk2;
    int size = 20;

    chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "Hello, World!");

    chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memcpy(chunk2, chunk1, size);

    printf("Contents of chunk2 after copy: %s\n", chunk2);

    free(chunk1);

    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    free(chunk2);

    return 0;
}