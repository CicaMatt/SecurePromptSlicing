#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]", buffer);
    if (result != EOF) {
        getchar(); // Consume the newline character
    }
    printf("Read %d characters: '%s'\n", result, buffer);
    return 0;
}