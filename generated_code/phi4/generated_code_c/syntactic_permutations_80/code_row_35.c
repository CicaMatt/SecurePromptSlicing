#include <stdio.h>
#include <string.h>

int scan(char *buffer, size_t bufferSize) {
    // Using a format string to specify that we want to read until a newline character,
    // but do not store the newline character itself in the buffer.
    int result = scanf("%1023[^\n]%*c", buffer);
    
    // Ensuring null-termination of the string
    if (result > 0) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }

    return result;
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    int charsRead = scan(buffer, sizeof(buffer));
    
    if(charsRead > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("No input was read.\n");
    }
    
    return 0;
}