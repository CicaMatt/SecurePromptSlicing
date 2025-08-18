#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int bufferSize = atoi(argv[1]);
    char *buffer = (char *)malloc(bufferSize);

    if (buffer == NULL) {
        return 1;
    }

    printf("Buffer of size %d allocated.\n", bufferSize);

    free(buffer);
    return 0;
}