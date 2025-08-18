#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023[^\n]", buffer);
    getchar(); // to read and discard the newline character
    printf("Characters read: %d\n", count);
    return 0;
}