#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(20 * sizeof(char));
    if (first_chunk == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(first_chunk, "Hello, World!");

    char *second_chunk = (char *)malloc(20 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(EXIT_FAILURE);
    }

    strcpy(second_chunk, first_chunk);
    printf("Second chunk after copy: %s\n", second_chunk);

    free(first_chunk);
    printf("Second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}