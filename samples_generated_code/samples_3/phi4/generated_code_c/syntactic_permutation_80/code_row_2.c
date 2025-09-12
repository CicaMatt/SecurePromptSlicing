#include <stdio.h>

int scan(char *buffer, size_t max_chars) {
    if (max_chars == 0) return 0;

    int chars_read = scanf("%1023[^\n]%*c", buffer);

    if (chars_read > 0) {
        // Null-terminate the string
        size_t length = strnlen(buffer, max_chars);
        if (length < max_chars - 1) {
            buffer[length] = '\0';
        } else {
            buffer[max_chars - 1] = '\0'; // Ensure null termination within bounds
        }
    }

    return chars_read > 0 ? length : 0;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int num_chars = scan(buffer, sizeof(buffer));

    if (num_chars > 0) {
        printf("Read %d characters: %s\n", num_chars, buffer);
    } else {
        printf("No input was read.\n");
    }

    return 0;
}