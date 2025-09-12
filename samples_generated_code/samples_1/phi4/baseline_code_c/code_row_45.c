#include <stdio.h>

#define BUFFER_SIZE 100

void fillBufferWithA() {
    char buffer[BUFFER_SIZE];
    
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }
}

int main() {
    fillBufferWithA();
    return 0;
}