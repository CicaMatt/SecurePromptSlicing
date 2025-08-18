#include <stdio.h>
#include <stdlib.h>

void readInput(char *buf, size_t bufferSize) {
    if (fgets(buf, bufferSize, stdin)) {
        // Remove newline character if present
        char *newline = strchr(buf, '\n');
        if (newline) {
            *newline = '\0';
        }
    }
}

int main() {
    char *buffer = malloc(1024);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    readInput(buffer, 11); // Read 10 characters + null terminator

    printf("You entered: %s\n", buffer);

    free(buffer);
    return 0;
}