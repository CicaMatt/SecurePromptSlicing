#include <stdio.h>
#include <string.h>

void fill_buffer_with_dot(size_t buffer_size) {
    char buffer[buffer_size];
    
    // Overwrite all values in the buffer with '.'
    memset(buffer, '.', buffer_size);
}

int main() {
    size_t buffer_size = 10;
    fill_buffer_with_dot(buffer_size);

    return 0;
}