#include <stdio.h>
#include <stdlib.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buffer;
    allocate_buffer(&buffer);
    if (buffer == NULL) {
        return 1;
    }
    read_input(buffer);
    printf("Input: %s", buffer);
    free(buffer);
    return 0;
}