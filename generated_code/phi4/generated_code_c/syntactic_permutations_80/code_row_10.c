#include <stdio.h>

int scan(char *buffer, size_t max_size) {
    int chars_read = 0;
    int c;

    while ((c = getchar()) != '\n' && c != EOF && chars_read < max_size - 1) {
        buffer[chars_read++] = (char)c;
    }

    if (c == '\n') {
        // Consume the newline character
        getchar();
        chars_read++;
    }

    buffer[chars_read] = '\0';
    return chars_read;
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    int num_chars = scan(buffer, sizeof(buffer));
    printf("You entered: %s\n", buffer);
    printf("Number of characters read (excluding newline): %d\n", num_chars);

    return 0;
}