#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(20);
    if (first_chunk == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(first_chunk, "Hello, World!");

    char *second_chunk = (char *)malloc(strlen(first_chunk) + 1);
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(EXIT_FAILURE);
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of the first chunk: %s\n", first_chunk);
    free(first_chunk);

    printf("Contents of the second chunk: %s\n", second_chunk);
    free(second_chunk);

    return 0;
}