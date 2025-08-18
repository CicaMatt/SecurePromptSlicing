#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]", buffer);
    if (result == 1) {
        printf("Read %d characters: %s\n", result, buffer);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}