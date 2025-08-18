#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string (will stop reading after newline): ");
    int chars_read = scanf("%1023[^\n]%*c", buffer);
    
    if (chars_read == 1) {
        printf("\nYou entered: %s\n", buffer);
    } else {
        printf("\nAn error occurred during input.\n");
    }
    
    return 0;
}