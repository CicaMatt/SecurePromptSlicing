#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int charsRead = scanf("%1023[^\\n]%*c", buffer);
    
    if (charsRead == 1) {
        printf("String read successfully.\n");
        printf("You entered: %s\n", buffer);
    } else {
        printf("An error occurred during input.\n");
    }

    return 0;
}