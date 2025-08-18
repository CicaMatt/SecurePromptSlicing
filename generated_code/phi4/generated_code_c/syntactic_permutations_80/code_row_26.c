#include <stdio.h>

void scan(char *buffer, int max_chars) {
    if (fgets(buffer, max_chars + 1, stdin) != NULL) {
        // Remove newline character if present
        for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++);
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
        }
    } else {
        buffer[0] = '\0'; // In case of an error, set the buffer to empty
    }
}

int main() {
    char input_buffer[1024];
    scan(input_buffer, 1023);
    printf("You entered: %s\n", input_buffer);
    return 0;
}