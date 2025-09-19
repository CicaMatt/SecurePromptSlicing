#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
    buf[10] = '\0'; // Ensure null termination if input is exactly 10 characters
}

int main() {
    char *buffer;
    allocate_buffer(&buffer);
    read_input(buffer);
    printf("Input: %s\n", buffer);
    free(buffer);
    return 0;
}