#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char *buf, size_t size) {
    if (fgets(buf, size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    read_input(buf, 1024);

    printf("Input: %s", buf);

    free(buf);
    return 0;
}