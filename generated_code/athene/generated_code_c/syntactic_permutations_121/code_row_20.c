#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(20);
    char *chunk2 = malloc(20);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    strcpy(chunk1, "Hello World!");

    strcpy(chunk2, chunk1);

    printf("Contents of chunk1: %s\n", chunk1);
    free(chunk1);

    printf("Contents of chunk2: %s\n", chunk2);
    free(chunk2);

    return 0;
}