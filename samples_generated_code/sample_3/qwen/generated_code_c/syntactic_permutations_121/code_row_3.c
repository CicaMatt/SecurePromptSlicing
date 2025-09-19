#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;

    first_chunk = (char *)malloc(10 * sizeof(char));
    if (first_chunk == NULL) {
        exit(1);
    }

    strcpy(first_chunk, "Hello");

    second_chunk = (char *)malloc(10 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(1);
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing the first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}