#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }

    strcpy(first_chunk, "HelloWorld");

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        perror("Failed to allocate second chunk");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    memcpy(second_chunk, first_chunk, size);

    free(first_chunk);
    
    strcpy(second_chunk, "Goodbye"); // Modify the content of second chunk

    printf("%s\n", second_chunk);

    free(second_chunk);

    return 0;
}