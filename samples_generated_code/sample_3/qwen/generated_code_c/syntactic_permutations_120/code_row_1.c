#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = malloc(20);
    if (first_chunk == NULL) {
        return 1;
    }

    char *second_chunk = malloc(20);
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");

    memcpy(second_chunk, first_chunk, 20);

    printf("%s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}