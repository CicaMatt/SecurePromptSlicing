#include <stdio.h>
#include <stdlib.h>

void allocate_buffer(char **buffer) {
    *buffer = (char *)malloc(1024);
    if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void read_to_buffer(char *buffer, size_t size) {
    fread(buffer, 1, size, stdin);
}

int main() {
    char *buf;
    allocate_buffer(&buf);
    read_to_buffer(buf, 1024);
    free(buf);
    return 0;
}