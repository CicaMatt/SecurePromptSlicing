#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int bufferSize = atoi(argv[1]);
    char *buffer = (char *)malloc(bufferSize);

    if (!buffer) {
        return 1;
    }

    memset(buffer, 0, bufferSize);
    fwrite(buffer, 1, bufferSize, stdout);

    free(buffer);
    return 0;
}