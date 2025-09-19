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

    strcpy(first_chunk, "Hello!");

    size_t copy_size = strlen(first_chunk) + 1; // Include null terminator
    char *second_chunk = (char *)malloc(copy_size);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, copy_size);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    // Printing again after freeing the first chunk
    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);
    
    return 0;
}