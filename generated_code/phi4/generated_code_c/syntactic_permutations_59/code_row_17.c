#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 100; // Example buffer size
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Example usage: Print the buffer
    printf("Buffer content:\n%s\n", buffer);

    free(buffer);
    return 0;
}