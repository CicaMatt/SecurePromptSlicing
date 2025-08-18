#include <stdio.h>
#include <stdlib.h>

void allocate_buffer() {
    char *buffer = malloc(1024);
    if (buffer == NULL) {
        exit(1);
    }
    read_input(buffer);
    free(buffer);
}

void read_input(char *buffer) {
    if (fgets(buffer, 11, stdin) != NULL) {
        buffer[10] = '\0'; // Ensure null-termination
    }
}

int main() {
    allocate_buffer();
    return 0;
}