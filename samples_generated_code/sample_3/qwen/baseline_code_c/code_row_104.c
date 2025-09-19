#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024);
    if (*buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void readInput(char *buf) {
    printf("Enter 10 characters: ");
    for (int i = 0; i < 10; i++) {
        buf[i] = getchar();
    }
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    printf("You entered: %.10s\n", buffer);
    free(buffer);
    return 0;
}