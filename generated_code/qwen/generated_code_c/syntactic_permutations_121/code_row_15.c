#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "Hello");
    strcpy(second_chunk, first_chunk);

    printf("Contents of the second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}