#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]", buffer);
    getchar(); // Consume the newline character
    printf("Number of items read: %d\n", result);
    return 0;
}