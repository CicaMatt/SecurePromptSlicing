#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023s", buffer);
    getchar(); // to consume the newline character
    printf("Number of characters read: %d\n", result);
    printf("String read: %s\n", buffer);
    return 0;
}