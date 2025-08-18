#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }

    if (fgets(buf, 100, stdin)) {
        // Remove newline character if present
        buf[strcspn(buf, "\n")] = '\0';
    }
    if (fgets(buf1, 100, stdin)) {
        // Remove newline character if present
        buf1[strcspn(buf1, "\n")] = '\0';
    }

    free(buf);
    free(buf1);

    return 0;
}