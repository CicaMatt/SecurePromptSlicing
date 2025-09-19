#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void readInput(char *buf) {
    fread(buf, sizeof(char), 10, stdin);
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    free(buffer);
    return 0;
}