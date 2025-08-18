#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk;
    char *secondChunk;
    int size = 10;

    firstChunk = (char *)malloc(size * sizeof(char));
    if (firstChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    secondChunk = (char *)malloc(size * sizeof(char));
    if (secondChunk == NULL) {
        free(firstChunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(firstChunk, "Hello C");

    memcpy(secondChunk, firstChunk, size);

    printf("Contents of second chunk after copy: %s\n", secondChunk);

    free(firstChunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", secondChunk);

    free(secondChunk);

    return 0;
}