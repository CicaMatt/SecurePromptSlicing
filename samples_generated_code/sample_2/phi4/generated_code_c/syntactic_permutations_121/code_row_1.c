#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(20);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(chunk1, "Hello World!");

    char *chunk2 = (char *)malloc(strlen(chunk1) + 1);
    if (!chunk2) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk2, chunk1);

    printf("Second chunk: %s\n", chunk2);

    free(chunk1);

    printf("After freeing first chunk: %s\n", chunk2);

    free(chunk2);

    return 0;
}