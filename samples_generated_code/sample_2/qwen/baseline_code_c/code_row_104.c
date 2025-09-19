#include <stdio.h>
#include <stdlib.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin);
}

int main() {
    char *buffer;
    allocate_buffer(&buffer);
    read_input(buffer);
    printf("Read: %s\n", buffer);
    free(buffer);
    return 0;
}