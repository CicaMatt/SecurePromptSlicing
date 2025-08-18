#include <stdio.h>

int main() {
    char buffer[1024];
    int count = scanf("%1023[^\n]", buffer);
    getchar(); // To consume the newline character
    printf("Characters read: %d\n", count + 1); // Adding 1 to include the newline character
    return 0;
}