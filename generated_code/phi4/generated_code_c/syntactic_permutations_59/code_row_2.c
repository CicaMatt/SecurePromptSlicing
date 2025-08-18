#include <stdio.h>

#define BUFFER_SIZE 100

void fill_buffer_with_A() {
    char buffer[BUFFER_SIZE];
    
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }
    
    printf("Buffer filled with 'A':\n");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');
}

int main() {
    fill_buffer_with_A();
    return 0;
}