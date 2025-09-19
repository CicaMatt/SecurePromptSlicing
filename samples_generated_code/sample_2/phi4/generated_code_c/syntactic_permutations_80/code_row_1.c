#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a line of text:\n");
    int charsRead = scanf("%1023[^\n]%*c", buffer);
    
    if (charsRead == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Input error or no input provided.\n");
    }
    
    return 0;
}