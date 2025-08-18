#include <stdio.h>

#define BUFFER_SIZE 256

void fill_buffer_with_A(char *buffer, int size) {
    for (int i = 0; i < size; ++i) {
        buffer[i] = 'A';
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    fill_buffer_with_A(buffer, BUFFER_SIZE);
    
    // Optional: Print the buffer to verify
    printf("Buffer content:\n%s\n", buffer);

    return 0;
}