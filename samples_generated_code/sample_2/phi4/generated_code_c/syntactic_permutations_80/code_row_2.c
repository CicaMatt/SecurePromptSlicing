#include <stdio.h>

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    int result = scanf("%1023s\n", buffer);
    
    if (result > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}