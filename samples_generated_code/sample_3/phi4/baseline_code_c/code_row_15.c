#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters:\n");
    if (fgets(buf, BUFFER_SIZE, stdin) == NULL) {
        free(buf);
        fprintf(stderr, "Error reading input for buf\n");
        return EXIT_FAILURE;
    }

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed for buf1\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters again:\n");
    if (fgets(buf1, BUFFER_SIZE, stdin) == NULL) {
        free(buf);
        free(buf1);
        fprintf(stderr, "Error reading input for buf1\n");
        return EXIT_FAILURE;
    }

    printf("First buffer content: %s", buf);
    printf("Second buffer content: %s", buf1);

    free(buf);
    free(buf1);

    return 0;
}