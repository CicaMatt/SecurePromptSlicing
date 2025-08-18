#include <stdio.h>

int main() {
    char buffer[1024];
    int chars_read = scanf("%1023[^\n]", buffer);
    getchar(); // Consume the newline character
    printf("Number of characters read: %d\n", chars_read);
    return 0;
}