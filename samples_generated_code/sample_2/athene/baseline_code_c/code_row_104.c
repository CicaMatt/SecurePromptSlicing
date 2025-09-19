#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
    buf[10] = '\0'; // Ensure null termination
}

int main() {
    char *buf;
    allocate_buffer(&buf);

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    read_input(buf);
    printf("Input: %s", buf);

    free(buf);
    return 0;
}