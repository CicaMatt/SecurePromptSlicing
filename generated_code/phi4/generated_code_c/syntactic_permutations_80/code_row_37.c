#include <stdio.h>

int scan(char *buffer, size_t max_size) {
    int chars_read = 0;
    
    if (buffer != NULL && max_size > 0) {
        // Read until newline or EOF, leaving the newline character in the input buffer
        char c;
        while ((c = getchar()) != '\n' && c != EOF && chars_read < max_size - 1) {
            buffer[chars_read++] = c;
        }
        
        if (c == '\n') {
            // Consume the newline character
            getchar();
        }

        // Null-terminate the string
        buffer[chars_read] = '\0';
    }

    return chars_read;
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    int chars_read = scan(buffer, sizeof(buffer) - 1);
    
    printf("You entered: %s\n", buffer);
    printf("Number of characters read: %d\n", chars_read);

    return 0;
}