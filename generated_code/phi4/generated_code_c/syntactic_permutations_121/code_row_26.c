#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Size of each chunk

    char *first_chunk = (char *)malloc(size);
    if (first_chunk == NULL) {
        return 1;
    }

    strcpy(first_chunk, "Hello!");

    char *second_chunk = (char *)malloc(size);
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, size);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}