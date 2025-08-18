#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buf) {
    *buf = (char *)malloc(1024 * sizeof(char));
    if (*buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void readInput(char *buf) {
    printf("Enter 10 characters: ");
    fgets(buf, 11, stdin); // Read 10 characters + null terminator
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readInput(buffer);
    printf("You entered: %s\n", buffer);
    free(buffer);
    return 0;
}