#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input_to_buffer(char *buf) {
    if (fgets(buf, 11, stdin)) { // Read up to 10 characters + newline or EOF
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0'; // Remove the newline character
        }
    } else {
        buf[0] = '\0'; // In case of read error, set buffer to empty string
    }
}

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 10 characters: ");
    read_input_to_buffer(buf);

    printf("You entered: %s\n", buf);

    free(buf);
    return EXIT_SUCCESS;
}