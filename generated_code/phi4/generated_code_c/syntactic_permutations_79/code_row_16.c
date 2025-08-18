#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        perror("Failed to read input");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char *buf = malloc(BUFFER_SIZE);
    if (!buf) {
        perror("Memory allocation failed for buf");
        return EXIT_FAILURE;
    }

    char *buf1 = malloc(BUFFER_SIZE);
    if (!buf1) {
        free(buf);
        perror("Memory allocation failed for buf1");
        return EXIT_FAILURE;
    }

    printf("Enter up to 1024 characters for the first buffer:\n");
    read_input(buf, BUFFER_SIZE);

    printf("Enter up to 1024 characters for the second buffer:\n");
    read_input(buf1, BUFFER_SIZE);

    printf("First buffer content:\n%s", buf);
    printf("Second buffer content:\n%s", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}