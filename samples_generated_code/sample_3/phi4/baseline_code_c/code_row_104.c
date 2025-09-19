#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input(char *buf) {
    if (fgets(buf, 11, stdin)) {
        // Null-terminate at the position of the newline or after reading 10 characters.
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';  // Remove the newline character
        }
    } else {
        buf[0] = '\0';
    }
}

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Please enter up to 10 characters:\n");
    read_input(buf);

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}