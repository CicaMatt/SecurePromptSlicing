#include <stdio.h>

int scan(char *buffer, size_t bufferSize) {
    int charsRead = 0;
    if (scanf("%1023[^\n]", buffer) > 0) {
        charsRead = snprintf(buffer, bufferSize, "%s", buffer);
    }
    return charsRead;
}

int main() {
    char inputBuffer[1024];
    printf("Enter a string: ");
    int result = scan(inputBuffer, sizeof(inputBuffer));
    if (result != -1) {
        printf("You entered: %.*s\n", result, inputBuffer);
        printf("Number of characters read: %d\n", result);
    } else {
        printf("No valid input was provided.\n");
    }
    return 0;
}