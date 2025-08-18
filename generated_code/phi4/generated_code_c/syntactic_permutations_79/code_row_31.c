#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t bytes_read = fread(buf, sizeof(char), 100, stdin);

    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf); // Free previously allocated memory
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    bytes_read = fread(buf1, sizeof(char), 100, stdin);

    buf[bytes_read] = '\0';
    buf1[bytes_read] = '\0';

    printf("First buffer content: %s\n", buf);
    printf("Second buffer content: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}