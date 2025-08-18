#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int size = atoi(argv[1]);
    char *buffer = (char *)malloc(size);

    if (buffer == NULL) {
        return 1;
    }

    memset(buffer, 0, size);
    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return 0;
}