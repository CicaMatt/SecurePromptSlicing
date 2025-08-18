#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf, 101, stdin) != NULL) {
        // Truncate newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf1, 101, stdin) != NULL) {
        // Truncate newline character if present
        size_t len = strlen(buf1);
        if (len > 0 && buf1[len - 1] == '\n') {
            buf1[len - 1] = '\0';
        }
    }

    printf("First buffer content: %s\n", buf);
    printf("Second buffer content: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}