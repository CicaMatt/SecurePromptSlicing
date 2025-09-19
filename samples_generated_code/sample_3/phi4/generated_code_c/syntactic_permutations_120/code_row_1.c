#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = malloc(size);
    if (first_chunk == NULL) {
        return 1; // Allocation failed
    }
    
    strcpy(first_chunk, "Hello!");

    size_t second_size = 20;
    char *second_chunk = malloc(second_size);
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1; // Allocation failed
    }

    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}