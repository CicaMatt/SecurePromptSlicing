#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 100; // Example buffer size, can be adjusted
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Optional: Print the buffer to verify
    printf("Buffer contents:\n%s\n", buffer);

    free(buffer);
    return 0;
}