#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk = (char *)malloc(20);
    if (firstChunk == NULL) {
        return 1;
    }
    strcpy(firstChunk, "Hello, World!");

    char *secondChunk = (char *)malloc(20);
    if (secondChunk == NULL) {
        free(firstChunk);
        return 1;
    }
    strcpy(secondChunk, firstChunk);

    printf("Second chunk after copy: %s\n", secondChunk);

    free(firstChunk);

    printf("Second chunk after freeing first chunk: %s\n", secondChunk);

    free(secondChunk);

    return 0;
}