#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(50 * sizeof(char));
    char *chunk2 = malloc(50 * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    strcpy(chunk1, "This is a test string to copy.");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("%s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}