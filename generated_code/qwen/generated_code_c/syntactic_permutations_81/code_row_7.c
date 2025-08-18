#include <stdio.h>
#include <stdlib.h>

void allocate_memory(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // 10 characters + null terminator
}

int main() {
    char *buffer;
    allocate_memory(&buffer);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    read_input(buffer);
    printf("Read: %s", buffer);
    free(buffer);
    return 0;
}