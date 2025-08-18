#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = malloc(BUFFER SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    size_t num_read1 = fread(buf, sizeof(char), BUFFER_SIZE, stdin);

    if (ferror(stdin)) {
        perror("Error reading standard input");
        free(buf);
        return EXIT_FAILURE;
    }

    buf[num_read1] = '\0';  // Null-terminate the string

    char *buf1 = malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    size_t num_read2 = fread(buf1, sizeof(char), BUFFER_SIZE, stdin);

    if (ferror(stdin)) {
        perror("Error reading standard input");
        free(buf);
        free(buf1);
        return EXIT_FAILURE;
    }

    buf1[num_read2] = '\0';  // Null-terminate the string

    printf("First buffer content: %.*s\n", num_read1, buf);
    printf("Second buffer content: %.*s\n", num_read2, buf1);

    free(buf);
    free(buf1);
    return EXIT_SUCCESS;
}