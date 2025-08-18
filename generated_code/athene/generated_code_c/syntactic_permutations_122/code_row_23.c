#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    memset(chunk1, 'A', 9); // Fill the first chunk with 'A'
    chunk1[9] = '\0';       // Null-terminate

    memcpy(chunk2, chunk1, 10);

    free(chunk1);
    free(chunk2);

    return 0;
}