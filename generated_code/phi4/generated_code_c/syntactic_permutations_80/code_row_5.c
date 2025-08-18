#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int numRead = scanf("%1023[^\n]%*c", buffer);
    
    if (numRead == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }
    
    return 0;
}