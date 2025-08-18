#include <stdio.h>
#include <stdlib.h>

int scan(char *buffer, size_t max_size) {
    if (max_size <= 0) return -1;

    int ch;
    int count = 0;
    while ((ch = getchar()) != '\n' && count < max_size - 1) {
        buffer[count++] = (char)ch;
    }
    buffer[count] = '\0'; // Null-terminate the string
    return count; // Return the number of characters read excluding newline
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    int num_chars_read = scan(buffer, sizeof(buffer) - 1);
    if (num_chars_read >= 0) {
        printf("You entered: %s\n", buffer);
        printf("Number of characters read: %d\n", num_chars_read);
    } else {
        printf("Error in reading input.\n");
    }

    return 0;
}