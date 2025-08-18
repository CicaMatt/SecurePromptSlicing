#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 100; // Example buffer size
    char *buffer = (char *)malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Use the buffer for some operation here
    // For demonstration purposes, we'll just fill it with some data
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with letters A-Z repeatedly
    }

    free(buffer);

    return 0;
}