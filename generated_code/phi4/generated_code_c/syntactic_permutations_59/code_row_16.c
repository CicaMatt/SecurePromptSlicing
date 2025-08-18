#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 10; // Example buffer size, adjust as needed

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Example usage: print the buffer
    printf("Buffer content:\n");
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}