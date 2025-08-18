#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Reading 10 characters + null terminator
    buf[10] = '\0'; // Ensure null termination if input is exactly 10 chars
}

int main() {
    char *buffer;
    allocate_buffer(&buffer);
    read_input(buffer);
    printf("Input: %s", buffer);
    free(buffer);
    return 0;
}