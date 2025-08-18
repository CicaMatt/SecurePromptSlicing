#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);
    printf("Number of characters read: %d\n", result);
    printf("String read: %s\n", buffer);
    return 0;
}