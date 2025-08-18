#include <stdio.h>

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    int numChars = scanf("%1023s", buffer);
    
    if (numChars == 1) {
        printf("Number of characters read: %d\n", numChars * (sizeof(buffer) - 1));
        printf("String read: %s\n", buffer);
    } else {
        printf("Failed to read input.\n");
    }
    
    return 0;
}