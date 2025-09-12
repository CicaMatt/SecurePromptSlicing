#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Example data for demonstration
    strcpy(chunk1, "abcdefgh");

    memcpy(chunk2, chunk1, 10);

    free(chunk1);
    free(chunk2);

    return 0;
}