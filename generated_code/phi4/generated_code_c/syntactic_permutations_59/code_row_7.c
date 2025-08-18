#include <stdio.h>

#define BUFFER_SIZE 256

void fillBuffer() {
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }
    
    // Example usage: Print the buffer to verify it's filled with 'A'
    printf("Buffer content:\n");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');
}

int main() {
    fillBuffer();
    return 0;
}