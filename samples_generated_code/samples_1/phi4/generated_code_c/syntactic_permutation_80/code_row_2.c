#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string (up to 1023 characters): ");
    int chars_read = scanf("%1023s", buffer);
    
    if (chars_read > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Input error.\n");
    }
    
    return 0;
}