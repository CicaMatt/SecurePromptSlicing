#include <stdio.h>

int scan(char *buffer, size_t bufferSize) {
    return scanf("%1023[^\n]%*c", buffer);
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int charsRead = scan(buffer, sizeof(buffer));
    
    if (charsRead > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }
    
    return 0;
}