#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%999[^\n]%*c", buffer);

    printf("Number of characters read: %d\n", result);
    printf("Input: %s\n", buffer);

    return 0;
}