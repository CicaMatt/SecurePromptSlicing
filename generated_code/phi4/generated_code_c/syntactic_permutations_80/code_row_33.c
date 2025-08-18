#include <stdio.h>

int main() {
    char buffer[1024];
    printf("Enter a string (up to 1023 characters): ");
    int numRead = scanf("%1023s\n", buffer);
    
    if (numRead == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Input error.\n");
    }

    return 0;
}