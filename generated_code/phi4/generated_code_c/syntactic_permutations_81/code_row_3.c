#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* allocate_buffer() {
    return (char*)malloc(BUFFER_SIZE * sizeof(char));
}

void read_from_stdin(char* buffer, size_t num_chars) {
    if (fgets(buffer, num_chars + 1, stdin)) {
        // Remove newline character if present
        char* newline = strchr(buffer, '\n');
        if (newline) {
            *newline = '\0';
        }
    } else {
        // Clear the buffer in case of read error
        buffer[0] = '\0';
    }
}

int main() {
    char* buf = allocate_buffer();
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    read_from_stdin(buf, 10);

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}