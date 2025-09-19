#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 11 // 10 characters + null terminator

void allocate_memory_and_read(char *buf) {
    if (buf == NULL) return;

    // Allocate memory for buffer
    buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter 10 characters: ");
    if (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        free(buf); // Free allocated memory on error
        exit(EXIT_FAILURE);
    }

    printf("Stored in buffer: %s\n", buf);

    // Free the allocated memory
    free(buf);
}

int main() {
    char *buffer = NULL;
    allocate_memory_and_read(buffer);
    return 0;
}