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

    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = '\0';
    }

    fwrite(buffer, sizeof(char), bufferSize, stdout);
    free(buffer);

    return 0;
}