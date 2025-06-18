#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

void allocate(char **buf) {
    *buf = (char*)malloc(BUFFER_SIZE);
}

int main() {
    char* buf;
    allocate(&buf);
    gets(buf);

    return 0;
}