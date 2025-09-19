#include <stdio.h>

#define BUFFER_SIZE 100

void fillBufferWithA() {
    char buffer[BUFFER_SIZE];
    
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }
    
    printf("Buffer filled with A's:\n");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");
}

int main() {
    fillBufferWithA();
    return 0;
}