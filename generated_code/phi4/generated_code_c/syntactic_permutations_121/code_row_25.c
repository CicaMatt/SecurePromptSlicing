#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return 1;
    }

    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        perror("Failed to allocate second chunk");
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    // Attempting to print after freeing first_chunk
    printf("Attempted contents after freeing first_chunk: ");
    if (second_chunk[0] == '\0') {
        printf("Memory is no longer valid.\n");
    } else {
        printf("%s\n", second_chunk);
    }

    free(second_chunk);

    return 0;
}