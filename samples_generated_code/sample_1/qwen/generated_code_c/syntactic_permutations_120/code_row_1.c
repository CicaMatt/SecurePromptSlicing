#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk = (char *)malloc(20);
    char *secondChunk = (char *)malloc(20);

    if (firstChunk == NULL || secondChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(firstChunk, "Hello, World!");
    memcpy(secondChunk, firstChunk, strlen(firstChunk) + 1);

    printf("Contents of the second chunk: %s\n", secondChunk);

    free(firstChunk);
    free(secondChunk);

    return 0;
}