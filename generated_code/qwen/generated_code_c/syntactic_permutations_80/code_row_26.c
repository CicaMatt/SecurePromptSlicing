#include <stdio.h>
#include <string.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    if (scanf("%1023[^\n]%*c", buffer) == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Failed to read input.\n");
    }
    
    return 0;
}