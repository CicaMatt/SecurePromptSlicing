#include <stdio.h>

int main() {
    int buffer_size = 10;
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = 'A';
    }

    for (int i = 0; i < buffer_size; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}