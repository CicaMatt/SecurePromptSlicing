#include <stdio.h>
#include <string.h>

int main() {
    int buffer_size = 1024;
    char buffer[buffer_size];
    memset(buffer, 'A', buffer_size);
    return 0;
}