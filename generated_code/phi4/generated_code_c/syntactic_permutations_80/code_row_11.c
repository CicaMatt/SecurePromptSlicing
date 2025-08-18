#include <stdio.h>
#define BUFFER_SIZE 1024

int scan(char *buffer) {
    int result = scanf("%1023[^\n]%*c", buffer);
    return result;
}

int main() {
    char inputBuffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    int charsRead = scan(inputBuffer);
    
    if (charsRead > 0) {
        printf("You entered: %s\n", inputBuffer);
    } else {
        printf("Failed to read input.\n");
    }
    
    return 0;
}