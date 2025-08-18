#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void allocateBuffer(char **buffer) {
    *buffer = (char *)malloc(BUFFER_SIZE);
    if (*buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

void readInput(char *buffer) {
    printf("Enter up to 10 characters: ");
    fgets(buffer, 11, stdin); // Reads at most 10 chars + newline
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline if present
}

int main() {
    char *buf = NULL;

    allocateBuffer(&buf);
    readInput(buf);

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}