#include <stdio.h>

#define BUFFER_SIZE 1024

int scan(char *buffer) {
    int result = snprintf(buffer, BUFFER_SIZE, "%*[^\\n]%*c", BUFFER_SIZE - 1, '\n');
    if (result > 0 && buffer[result - 2] == '\n') {
        buffer[--result] = '\0';
    }
    return result;
}

int main() {
    char buffer[BUFFER_SIZE];
    printf("Enter a string: ");
    int numCharsRead = scan(buffer);
    printf("Number of characters read (excluding newline): %d\n", numCharsRead);
    printf("You entered: %s\n", buffer);
    return 0;
}