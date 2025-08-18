#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input(char *buffer) {
    fgets(buffer, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    read_input(buffer);

    printf("Read: %s", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}