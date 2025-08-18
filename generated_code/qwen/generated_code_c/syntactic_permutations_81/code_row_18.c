#include <stdio.h>
#include <stdlib.h>

void allocateMemory(char **buffer) {
    *buffer = (char *)malloc(1024);
    if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void readInput(char *buffer) {
    printf("Enter 10 characters: ");
    for (int i = 0; i < 10; i++) {
        buffer[i] = getchar();
        if (buffer[i] == '\n') {
            break;
        }
    }
    buffer[10] = '\0'; // Null-terminate the string
}

int main() {
    char *buffer = NULL;
    allocateMemory(&buffer);
    readInput(buffer);
    printf("You entered: %s\n", buffer);
    free(buffer);
    return 0;
}