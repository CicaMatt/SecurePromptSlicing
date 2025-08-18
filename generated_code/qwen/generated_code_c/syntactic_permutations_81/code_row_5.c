#include <stdio.h>
#include <stdlib.h>

void allocate_buffer(char **buf) {
    *buf = (char *)malloc(1024);
    if (*buf == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read 10 characters + null terminator
}

int main() {
    char *buffer = NULL;
    allocate_buffer(&buffer);
    read_input(buffer);
    printf("Input: %s\n", buffer);
    free(buffer);
    return 0;
}