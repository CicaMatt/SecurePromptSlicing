#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        return 1;
    }

    char *buffer = (char *)malloc(size);
    if (!buffer) {
        return 1;
    }

    printf("Buffer of size %d allocated.\n", size);

    free(buffer);

    return 0;
}