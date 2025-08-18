#include <stdio.h>

int main() {
    size_t buffer_size = 10; // Example buffer size

    // Allocate buffer on the stack
    char buffer[buffer_size];

    // Overwrite all values in the buffer with 'A'
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Print the buffer to verify
    printf("Buffer: ");
    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}