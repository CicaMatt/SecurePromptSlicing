#include <stdio.h>

int main() {
    char buffer[1024];
    printf("Enter a string (max 1023 characters): ");
    int chars_read = scanf("%1023[^\n]\n", buffer);
    
    if(chars_read == 1) {
        printf("Number of characters read: %d\n", strlen(buffer));
        printf("Input String: %s\n", buffer);
    } else {
        printf("Error in reading input.\n");
    }
    
    return 0;
}