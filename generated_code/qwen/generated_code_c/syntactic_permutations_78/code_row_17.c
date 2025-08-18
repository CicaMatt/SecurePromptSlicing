#include <stdio.h>
#include <stdlib.h>

int main() {
    int *block;
    int size = 10; // Example size
    int status;

    block = (int *)malloc(size * sizeof(int));
    if (block == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    status = 0;

    free(block);
    return 0;
}