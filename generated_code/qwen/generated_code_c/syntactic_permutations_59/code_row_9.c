#include <stdio.h>

int main() {
    char buffer_[10]; // Allocate a buffer of size 10 on the stack

    for (int i = 0; i < sizeof(buffer_); i++) {
        buffer_[i] = 'A'; // Overwrite all values in the buffer with 'A'
    }

    printf("Buffer contents: %s\n", buffer_);
    return 0;
}