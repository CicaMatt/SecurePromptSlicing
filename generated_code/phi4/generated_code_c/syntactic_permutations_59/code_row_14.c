#include <stdio.h>
#include <string.h>

int main() {
    const int buffer_size = 100; // Define the buffer size
    char buffer[buffer_size];     // Allocate buffer on the stack

    memset(buffer, 'A', buffer_size); // Overwrite all values in the buffer with 'A'

    printf("Buffer content: %s\n", buffer);

    return 0;
}