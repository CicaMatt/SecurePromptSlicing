#include <stdio.h>

int main() {
    char buffer[1024];
    int chars_read;

    printf("Enter a line of text: ");
    
    chars_read = scanf("%1023[^\n]%*c", buffer);
    
    if (chars_read == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}