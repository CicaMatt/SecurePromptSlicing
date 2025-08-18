#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(20);
    if (chunk1 == NULL) return 1;
    strcpy(chunk1, "Hello, World!");

    char *chunk2 = malloc(20);
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }

    strcpy(chunk2, chunk1);

    printf("%s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}