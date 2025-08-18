#include <stdio.h>

int main() {
    int buffer_size = 100;
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = 'A';
    }

    return 0;
}