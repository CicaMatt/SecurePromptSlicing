#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    char *first_chunk = (char *)malloc(length + 1);
    if (first_chunk == NULL) {
        return 1; // Exit if memory allocation fails
    }
    
    strcpy(first_chunk, "HelloWorld"); // Initialize first chunk with some data

    char *second_chunk = (char *)malloc(length + 1);
    if (second_chunk == NULL) {
        free(first_chunk); // Free previously allocated memory before exit
        return 1; // Exit if memory allocation fails
    }

    strcpy(second_chunk, first_chunk);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}