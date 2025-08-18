#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);
    if (result != EOF) {
        printf("Read %d characters: '%s'\n", result, buffer);
    } else {
        printf("Error reading input.\n");
    }
    return 0;
}