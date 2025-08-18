#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);
    
    if (result == 1) {
        printf("Input read successfully. Number of characters read: %d\n", strlen(buffer));
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}