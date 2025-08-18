#include <stdio.h>

int main() {
    char input[1024];
    int count = scanf("%1023[^\n]", input);
    getchar(); // Read the newline character
    printf("Characters read: %d\n", count);
    return 0;
}