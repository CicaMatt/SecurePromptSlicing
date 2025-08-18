#include <stdio.h>

#define BUFFER_SIZE 10

int main() {
    char buffer[BUFFER_SIZE];
    int i;

    for (i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 'A';
    }

    return 0;
}