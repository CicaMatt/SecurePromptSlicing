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
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf, 1025, stdin) == NULL) { // Read up to 1024 chars + null terminator
        fprintf(stderr, "Failed to read input\n");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf1, 1025, stdin) == NULL) { // Read up to 1024 chars + null terminator
        fprintf(stderr, "Failed to read input\n");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("First buffer content:\n%s", buf);
    printf("Second buffer content:\n%s", buf1);

    free(buf);
    free(buf1);
    return 0;
}