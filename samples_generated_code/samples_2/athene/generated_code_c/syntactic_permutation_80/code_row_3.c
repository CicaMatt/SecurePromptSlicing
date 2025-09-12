#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]", buffer);
    getchar(); // Read the newline character
    printf("Characters read: %d\n", result);
    return 0;
}