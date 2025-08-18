#include <stdio.h>

int main() {
    int buffer_size = 10; // Example buffer size, adjust as needed
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Optionally print the buffer to verify contents
    for (int i = 0; i < buffer_size; ++i) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    return 0;
}