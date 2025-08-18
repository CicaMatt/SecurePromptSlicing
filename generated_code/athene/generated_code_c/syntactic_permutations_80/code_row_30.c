#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]", buffer);
    getchar(); // Consume newline character
    printf("%d\n", result);
    return 0;
}