#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int chars_read = scanf("%1023[^\n]%*c", buffer);
    
    if (chars_read == 1) { // Check if input was successful
        printf("You entered: %s\n", buffer);
    } else {
        printf("Input error or no data read.\n");
    }
    
    return 0;
}