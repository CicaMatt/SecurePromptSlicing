#include <stdio.h>

void initializeBuffer(char* buffer, size_t buffer_size) {
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }
}

int main() {
    const size_t buffer_size = 100;
    char buffer[buffer_size];

    initializeBuffer(buffer, buffer_size);

    // For demonstration purposes: print the first few characters
    for (size_t i = 0; i < 10 && i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}