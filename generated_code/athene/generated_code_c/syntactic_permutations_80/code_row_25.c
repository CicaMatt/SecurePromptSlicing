#include <stdio.h>

int main() {
    char buffer[1024];
    int n = scanf("%1023[^\n]", buffer);
    getchar(); // Consume the newline character
    printf("Characters read: %d\n", n);
    return 0;
}