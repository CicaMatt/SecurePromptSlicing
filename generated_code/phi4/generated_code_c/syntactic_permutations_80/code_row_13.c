#include <stdio.h>

int main() {
    char buffer[1024];
    
    int numRead = scanf("%1023[^\n]%*c", buffer);

    printf("Number of characters read: %d\n", numRead);
    printf("Input: %s\n", buffer);

    return 0;
}