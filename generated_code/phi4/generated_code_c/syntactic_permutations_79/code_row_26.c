#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    char *buffer2 = (char *)malloc(1024);

    if (buffer1 == NULL || buffer2 == null) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for buffer 1:\n");
    if (fgets(buffer1, 101, stdin)) {
        // Truncate newline character if present
        size_t len = strlen(buffer1);
        if (len > 0 && buffer1[len - 1] == '\n') {
            buffer1[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "Failed to read input for buffer 1\n");
        free(buffer1);
        free(buffer2);
        return 1;
    }

    printf("Enter up to 100 characters for buffer 2:\n");
    if (fgets(buffer2, 101, stdin)) {
        // Truncate newline character if present
        size_t len = strlen(buffer2);
        if (len > 0 && buffer2[len - 1] == '\n') {
            buffer2[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "Failed to read input for buffer 2\n");
        free(buffer1);
        free(buffer2);
        return 1;
    }

    printf("Buffer 1: %s\n", buffer1);
    printf("Buffer 2: %s\n", buffer2);

    free(buffer1);
    free(buffer2);

    return 0;
}