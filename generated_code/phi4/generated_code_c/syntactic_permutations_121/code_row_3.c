#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate first_chunk");
        return EXIT_FAILURE;
    }
    
    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        perror("Failed to allocate second_chunk");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, size);

    printf("Contents of the second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing first_chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}