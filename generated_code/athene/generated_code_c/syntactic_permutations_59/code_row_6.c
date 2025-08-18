#include <stdio.h>
#include <string.h>

int main() {
    size_t buffer_size = 1024;
    char buffer[buffer_size];
    memset(buffer, 'A', buffer_size - 1);
    buffer[buffer_size - 1] = '\0';
    return 0;
}