#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    // Example usage: Fill the buffer with some data
    for (size_t i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A';
    }
    buffer[buffer_size - 1] = '\0'; // Null-terminate the string

    printf("Buffer content: %s\n", buffer);

    free(buffer);
    return 0;
}