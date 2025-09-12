#include <stdio.h>

int scan(char *buffer, size_t size) {
    int chars_read = 0;
    if (fgets(buffer, size, stdin)) {
        for (chars_read = 0; buffer[chars_read] != '\n' && buffer[chars_read] != '\0'; ++chars_read);
        if (buffer[chars_read] == '\n') {
            // Remove the newline character from the buffer
            buffer[chars_read] = '\0';
        }
    }
    return chars_read;
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    int result = scan(buffer, sizeof(buffer));
    printf("You entered: %s\n", buffer);
    printf("Number of characters read (excluding newline): %d\n", result);

    return 0;
}