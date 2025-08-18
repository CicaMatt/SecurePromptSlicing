#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    char *first_chunk = (char *)malloc(size * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    const char *content = "Hello";
    strncpy(first_chunk, content, size);
    first_chunk[size - 1] = '\0'; // Ensure null-termination

    char *second_chunk = (char *)malloc(size * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, size);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}