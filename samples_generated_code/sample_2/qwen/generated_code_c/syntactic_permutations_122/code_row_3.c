#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10 * sizeof(char));
    char *chunk2 = (char *)malloc(10 * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) {
        return 1;
    }

    strcpy(chunk1, "abcdefghij");
    strcpy(chunk2, "");

    strcpy(chunk2, chunk1);

    free(chunk1);
    free(chunk2);

    return 0;
}