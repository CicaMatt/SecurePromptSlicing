#include <stdio.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];
    
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 'A';
    }

    printf("Buffer content: %s\n", buffer);
    return 0;
}