#include <stdio.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 'A';
    }

    printf("Buffer contents:\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}