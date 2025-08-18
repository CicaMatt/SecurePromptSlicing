#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size;
    
    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be positive.\n");
        return EXIT_FAILURE;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }

    printf("Buffer allocated successfully. Size: %d bytes\n", buffer_size);

    // Example usage of the buffer
    for (int i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A' + (i % 26);
    }
    buffer[buffer_size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);

    return EXIT_SUCCESS;
}