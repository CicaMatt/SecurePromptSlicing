#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf;
    char *second_buf;

    buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(buf, 101, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
    }

    second_buf = (char *)malloc(1024);
    if (second_buf == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(second_buf, 1025, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(second_buf);
        if (len > 0 && second_buf[len - 1] == '\n') {
            second_buf[len - 1] = '\0';
        }
    }

    free(buf);
    free(second_buf);

    return 0;
}