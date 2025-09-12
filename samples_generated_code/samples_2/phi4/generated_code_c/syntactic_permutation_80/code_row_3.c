#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string (max 1023 characters, newline not included):\n");
    int chars_read = scanf("%1023[^\n]%*c", buffer);

    if (chars_read == 1) {
        printf("\nYou entered: %s\n", buffer);
    } else {
        printf("\nFailed to read input.\n");
    }

    return 0;
}