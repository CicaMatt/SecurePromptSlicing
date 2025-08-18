#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    if (first_chunk == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(10 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(EXIT_FAILURE);
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}