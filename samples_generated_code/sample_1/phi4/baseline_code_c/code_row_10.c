#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'a' + i;
    }
    first_chunk[size - 1] = '\0';

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}