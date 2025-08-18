#include <stdio.h>

int main() {
    const int buffer_size = 100; // Example size, change as needed
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Optional: print the buffer to verify
    printf("%.*s\n", buffer_size, buffer);

    return 0;
}