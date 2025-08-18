#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return EXIT_FAILURE;
    }

    int chars_read = fread(buf, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        free(buf);
        perror("Error reading from stdin");
        return EXIT_FAILURE;
    }
    buf[chars_read] = '\0'; // Null-terminate the string

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed for buf1\n");
        free(buf);
        return EXIT_FAILURE;
    }

    chars_read = fread(buf1, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        perror("Error reading from stdin");
        free(buf);
        free(buf1);
        return EXIT_FAILURE;
    }
    buf1[chars_read] = '\0'; // Null-terminate the string

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}