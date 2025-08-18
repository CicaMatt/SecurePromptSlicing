#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input_to_buffer(char *buf) {
    fgets(buf, 11, stdin);
}

int main() {
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 10 characters: ");
    read_input_to_buffer(buffer);

    printf("You entered: %s", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}