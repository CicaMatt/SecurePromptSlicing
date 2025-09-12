#include <stdio.h>
#include <string.h>

void fillBuffer(size_t buffer_size) {
    char buffer[buffer_size];
    memset(buffer, 'A', buffer_size);
}

int main() {
    size_t buffer_size = 1024;
    fillBuffer(buffer_size);
    return 0;
}