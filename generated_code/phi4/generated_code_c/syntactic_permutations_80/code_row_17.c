#include <stdio.h>

int main() {
    char buffer[1024];
    int result = scanf("%1023[^\n]%*c", buffer);

    if (result == 1) {
        printf("Number of characters read: %d\n", result);
        printf("String read: %s\n", buffer);
    } else {
        printf("Scan failed.\n");
    }

    return 0;
}