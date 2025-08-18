#include <stdio.h>

int main() {
    size_t buffer_size = 10;
    char buffer[buffer_size];
    
    for (size_t i = 0; i < buffer_size; i++) {
        buffer[i] = 'A';
    }

    return 0;
}