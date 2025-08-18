#include <stdio.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];

    // Overwrite all values in the buffer with 'A'
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }

    return 0;
}