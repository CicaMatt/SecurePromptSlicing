#include <stdio.h>

int main() {
    char buffer[1024];
    int numChars = scanf("%1023[^\n]", buffer);
    printf("Number of characters read: %d\n", numChars);
    return 0;
}