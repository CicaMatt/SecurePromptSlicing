#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void fillBufferWithA() {
    char buffer[BUFFER_SIZE];
    memset(buffer, 'A', BUFFER_SIZE);
    
    // Optional: Print buffer content to verify (for demonstration purposes)
    printf("Buffer filled with 'A':\n%s\n", buffer);
}

int main() {
    fillBufferWithA();
    return 0;
}