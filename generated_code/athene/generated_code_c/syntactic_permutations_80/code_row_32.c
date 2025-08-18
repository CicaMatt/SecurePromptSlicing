#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023[^\n]", buffer);
    getchar(); // Consume the newline character
    printf("Read %d characters: %s\n", count, buffer);
    return 0;
}