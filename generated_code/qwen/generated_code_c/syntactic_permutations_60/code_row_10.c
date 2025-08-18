#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int size = atoi(argv[1]);
    char *buffer = (char *)malloc(size);

    if (buffer == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        buffer[i] = 'A';
    }

    fwrite(buffer, sizeof(char), size, stdout);
    free(buffer);

    return 0;
}