#include <stdio.h>

int main() {
    char buffer[1024];
    
    // Reading a string until newline, excluding the newline character itself.
    int numRead = scanf("%1023s", buffer);
    
    if (numRead == 1) {
        printf("Number of characters read: %d\n", numRead * sizeof(char));
        printf("String entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }
    
    return 0;
}