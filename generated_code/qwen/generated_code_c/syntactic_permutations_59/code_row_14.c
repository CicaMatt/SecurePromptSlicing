#include <stdio.h>

int main() {
    int buffer_size = 10;
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = 'A';
    }

    printf("Buffer contents: %s\n", buffer);
    return 0;
}