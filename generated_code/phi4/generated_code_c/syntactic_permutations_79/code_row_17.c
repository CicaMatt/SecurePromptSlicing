#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return EXIT_FAILURE;
    }

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed for buf1\n");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 1024 characters for the first buffer:\n");
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL && !feof(stdin)) {
        fprintf(stderr, "Error reading from standard input\n");
        free(buf);
        free(buf1);
        return EXIT_FAILURE;
    }

    printf("Enter up to 1024 characters for the second buffer:\n");
    if (fgets(buf1, BUFFER_SIZE, stdin) == NULL && !feof(stdin)) {
        fprintf(stderr, "Error reading from standard input\n");
        free(buf);
        free(buf1);
        return EXIT_FAILURE;
    }

    printf("First buffer content: %s", buf);
    printf("Second buffer content: %s", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}