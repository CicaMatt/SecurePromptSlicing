#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    char buffer_[BUFFER_SIZE];
    
    memset(buffer_, 'A', BUFFER_SIZE);
    
    // Just to demonstrate that all characters are set to 'A'
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        printf("%c", buffer_[i]);
    }
    
    return 0;
}