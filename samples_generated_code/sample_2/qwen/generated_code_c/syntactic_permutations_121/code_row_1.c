#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk = (char *)malloc(20 * sizeof(char));
    char *secondChunk = (char *)malloc(20 * sizeof(char));

    if (firstChunk == NULL || secondChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(firstChunk, "Hello, World!");

    strcpy(secondChunk, firstChunk);
    printf("Second chunk after copy: %s\n", secondChunk);

    free(firstChunk);
    printf("Second chunk after freeing first chunk: %s\n", secondChunk);

    free(secondChunk);

    return 0;
}