#include <stdio.h>
#include <stdlib.h>

void read_chars_to_buffer(char *buf) {
    if (fgets(buf, 11, stdin) != NULL) { // 11 to account for the null terminator
        int length = strlen(buf);
        if (buf[length - 1] == '\n') {
            buf[length - 1] = '\0'; // Remove newline character if present
        }
    }
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    read_chars_to_buffer(buf);

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}