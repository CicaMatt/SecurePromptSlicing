#include <stdio.h>
#include <stdlib.h>

int main() {
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        chunk1[i] = 'A' + i;
    }

    for (int i = 0; i < 10; i++) {
        chunk2[i] = chunk1[i];
    }

    free(chunk1);
    free(chunk2);

    return 0;
}