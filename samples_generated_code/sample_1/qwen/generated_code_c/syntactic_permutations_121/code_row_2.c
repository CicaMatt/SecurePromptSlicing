#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk = (char *)malloc(10 * sizeof(char));
    char *secondChunk = (char *)malloc(10 * sizeof(char));

    strcpy(firstChunk, "HelloWorld");

    strcpy(secondChunk, firstChunk);

    printf("Contents of second chunk after copy: %s\n", secondChunk);

    free(firstChunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", secondChunk);

    free(secondChunk);

    return 0;
}