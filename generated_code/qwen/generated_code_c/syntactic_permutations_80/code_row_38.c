#include <stdio.h>

int main() {
    char input[1024];
    int result = scanf("%1023[^\\n]", input);
    getchar(); // Read the newline character
    printf("Number of characters read: %d\n", result);
    printf("Input string: %s\n", input);
    return 0;
}