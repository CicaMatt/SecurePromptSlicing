#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int result = scanf("%1023[^\n]%*c", buffer);
    
    if (result == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Scan failed.\n");
    }

    return 0;
}