#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024);
    if (*buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void readInput(char *buf) {
    printf("Enter 10 characters: ");
    for (int i = 0; i < 10; ++i) {
        buf[i] = getchar();
        if (buf[i] == '\n') {
            break;
        }
    }
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    printf("You entered: ");
    for (int i = 0; i < 10 && buffer[i] != '\n'; ++i) {
        putchar(buffer[i]);
    }
    printf("\n");
    free(buffer);
    return 0;
}