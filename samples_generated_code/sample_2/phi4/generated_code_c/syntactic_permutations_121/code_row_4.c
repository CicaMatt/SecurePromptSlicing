#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        perror("Failed to allocate memory");
        return 1;
    }

    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate memory");
        return 1;
    }

    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of the second chunk after freeing first: %s\n", second_chunk);

    free(second_chunk);
    return 0;
}