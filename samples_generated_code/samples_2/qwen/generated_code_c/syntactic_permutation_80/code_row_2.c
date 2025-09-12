#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\\n]", buffer);
    getchar(); // Read and discard the newline character
    printf("Number of characters read: %d\n", result);
    printf("Buffer content: '%s'\n", buffer);
    return 0;
}