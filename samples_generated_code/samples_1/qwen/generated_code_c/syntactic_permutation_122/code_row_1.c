#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(100);
    char *chunk2 = (char *)malloc(100);

    if (chunk1 == NULL || chunk2 == NULL) {
        exit(EXIT_FAILURE);
    }

    strcpy(chunk1, "Hello, World!");
    strcpy(chunk2, chunk1);

    free(chunk1);
    free(chunk2);

    return 0;
}