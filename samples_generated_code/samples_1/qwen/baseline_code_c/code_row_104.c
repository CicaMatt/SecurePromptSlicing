#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buffer) {
    *buffer = (char *)malloc(1024 * sizeof(char));
    if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void readInput(char *buf) {
    printf("Enter 10 characters: ");
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    free(buffer);
    return 0;
}