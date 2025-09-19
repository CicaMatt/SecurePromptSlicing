#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    int bufferSize = atoi(argv[1]);
    char *buffer = (char *)malloc(bufferSize);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    printf("Buffer of size %d allocated\n", bufferSize);

    free(buffer);
    return EXIT_SUCCESS;
}