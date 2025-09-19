#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    int size = 10;

    first_chunk = (char *)malloc(size * sizeof(char));
    if (first_chunk == NULL) {
        return 1;
    }

    strcpy(first_chunk, "Hello");

    second_chunk = (char *)malloc(size * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}