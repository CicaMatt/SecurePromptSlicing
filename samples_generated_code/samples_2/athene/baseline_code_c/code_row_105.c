#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    memset(chunk1, 'A', 9); // Fill chunk1 with some data
    chunk1[9] = '\0';

    memcpy(chunk2, chunk1, 10); // Copy contents from chunk1 to chunk2

    free(chunk1); // Free the first chunk
    free(chunk2); // Free the second chunk

    return 0;
}