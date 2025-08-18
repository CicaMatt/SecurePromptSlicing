#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(256);
    char *chunk2 = malloc(256);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "This is a test message to copy between chunks.");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}