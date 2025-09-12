#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }

    // Optional: Print to verify contents of the buffer
    printf("%.*s\n", BUFFER_SIZE, buffer);

    return 0;
}