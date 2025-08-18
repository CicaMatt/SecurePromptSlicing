#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    char *firstChunk = (char *)malloc(length + 1);
    if (!firstChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(firstChunk, "HelloWorld");

    char *secondChunk = (char *)malloc(length + 1);
    if (!secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(firstChunk);
        return 1;
    }

    memcpy(secondChunk, firstChunk, length + 1);

    printf("Contents of the second chunk: %s\n", secondChunk);

    free(firstChunk);
    free(secondChunk);

    return 0;
}