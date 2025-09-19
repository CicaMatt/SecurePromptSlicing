#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(20 * sizeof(char));
    char *second_chunk = (char *)malloc(20 * sizeof(char));

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "Hello, World!");
    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    first_chunk = NULL;

    printf("Contents of the second chunk after freeing the first chunk: %s\n", second_chunk);

    free(second_chunk);
    second_chunk = NULL;

    return 0;
}