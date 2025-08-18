#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_from_stdin(char *buffer, size_t max_read) {
    if (fgets(buffer, max_read + 1, stdin) == NULL) {
        perror("Failed to read from standard input");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    printf("Enter up to 10 characters: ");
    read_from_stdin(buffer, 10);

    printf("You entered: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}