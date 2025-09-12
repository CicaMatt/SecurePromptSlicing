#include <stdio.h>

int scan(char *buffer) {
    return scanf("%1022[^\n]%*c", buffer);
}

int main() {
    char inputBuffer[1024];
    
    printf("Enter a string: ");
    int charsRead = scan(inputBuffer);

    if (charsRead > 0) {
        printf("You entered: %s\n", inputBuffer);
    } else {
        printf("Failed to read the input.\n");
    }

    return 0;
}