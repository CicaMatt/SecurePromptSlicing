#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(10);
    char *chunk2 = malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    memcpy(chunk2, chunk1, 10);

    free(chunk1);
    free(chunk2);

    return 0;
}