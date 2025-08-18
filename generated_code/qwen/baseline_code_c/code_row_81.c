#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024 * sizeof(char));
}

void readInput(char *buf) {
    fgets(buf, 11, stdin);
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    printf("Read: %s\n", buffer);
    free(buffer);
    return 0;
}