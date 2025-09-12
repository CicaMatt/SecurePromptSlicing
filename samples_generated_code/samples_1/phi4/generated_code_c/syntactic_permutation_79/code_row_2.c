#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    // Copy 100 characters to the first buffer
    for (int i = 0; i < 100; ++i) {
        buf[i] = 'A' + (i % 26); // Example: A, B, C, ..., Z, A, ...
    }
    buf[99] = '\0'; // Null-terminate

    // Copy 100 characters to the second buffer
    for (int i = 0; i < 100; ++i) {
        buf1[i] = 'a' + (i % 26); // Example: a, b, c, ..., z, a, ...
    }
    buf1[99] = '\0'; // Null-terminate

    printf("Content of first buffer:\n%s\n", buf);
    printf("Content of second buffer:\n%s\n", buf1);

    // Read up to 1024 characters from standard input
    char *inputBuffer = (char *)malloc(1024);
    if (!inputBuffer) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("Enter text (up to 1023 characters):\n");
    if (fgets(inputBuffer, 1024, stdin)) {
        // Remove newline character from fgets input
        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') {
            inputBuffer[len - 1] = '\0';
        }

        printf("You entered:\n%s\n", inputBuffer);
    } else {
        fprintf(stderr, "Error reading input\n");
    }

    free(buf);
    free(buf1);
    free(inputBuffer);

    return 0;
}