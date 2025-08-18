#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int chars_read = fread(buf, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        free(buf);
        fprintf(stderr, "Error reading from standard input\n");
        return 1;
    }

    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    chars_read = fread(buf1, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        free(buf);
        free(buf1);
        fprintf(stderr, "Error reading from standard input\n");
        return 1;
    }

    // Optionally print the buffers to verify
    printf("Buffer 1: %.*s\n", chars_read, buf);
    printf("Buffer 2: %.*s\n", chars_read, buf1);

    free(buf);
    free(buf1);
    return 0;
}