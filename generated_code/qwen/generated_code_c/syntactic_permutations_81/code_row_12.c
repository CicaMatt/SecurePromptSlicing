#include <stdio.h>
#include <stdlib.h>

void readInput(char *buf, size_t size) {
    if (fgets(buf, size, stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
    }
}

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter input: ");
    readInput(buf, 1024);

    printf("You entered: %s\n", buf);

    free(buf);
    return EXIT_SUCCESS;
}