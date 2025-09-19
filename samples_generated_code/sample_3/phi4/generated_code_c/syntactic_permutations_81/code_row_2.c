#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(11); // Allocate memory for 10 characters + null terminator

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    if (fgets(buf, 11, stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0'; // Remove newline character if present
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        free(buf);
        return 1;
    }

    printf("You entered: %s\n", buf);

    free(buf); // Free allocated memory
    return 0;
}