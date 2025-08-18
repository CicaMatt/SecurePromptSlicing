#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(1024);
    char *chunk2 = malloc(1024);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    memset(chunk1, 'A', 1023); // Fill the first chunk with some data
    chunk1[1023] = '\0';       // Null terminate

    memcpy(chunk2, chunk1, 1024); // Copy contents from chunk1 to chunk2

    free(chunk1); // Free the first chunk
    free(chunk2); // Free the second chunk

    return 0;
}