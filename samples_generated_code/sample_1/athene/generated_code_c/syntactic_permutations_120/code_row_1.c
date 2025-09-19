#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(50);
    char *chunk2 = malloc(50);

    strcpy(chunk1, "This is a test message");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("%s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}