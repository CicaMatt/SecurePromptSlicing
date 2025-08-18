#include <stdio.h>

void fillBuffer(char *buffer, int bufferSize) {
    for (int i = 0; i < bufferSize; ++i) {
        buffer[i] = 'A';
    }
}

int main() {
    const int buffer_size = 100;
    char buffer[buffer_size];

    fillBuffer(buffer, buffer_size);

    printf("Buffer content:\n%s\n", buffer);
    
    return 0;
}