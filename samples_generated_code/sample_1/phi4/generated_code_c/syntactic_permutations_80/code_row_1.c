#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);
    
    if (result == 1) {
        printf("Number of characters read: %d\n", result * 1023);
        printf("String entered: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}