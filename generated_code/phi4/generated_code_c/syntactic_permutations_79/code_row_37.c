#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void read_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    } else {
        buffer[0] = '\0'; // Clear buffer on EOF or error
    }
}

int main() {
    char *buf = malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    read_input(buf, BUFFER_SIZE);

    char *buf1 = malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    read_input(buf1, BUFFER_SIZE);

    printf("First input: %s\n", buf);
    printf("Second input: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}