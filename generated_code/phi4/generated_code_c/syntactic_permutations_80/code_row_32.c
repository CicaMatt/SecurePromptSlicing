#include <stdio.h>

int main() {
    char buffer[1024];
    int numRead = scanf("%1023s\n", buffer);

    if (numRead == 1) {
        printf("Number of characters read: %d\n", strlen(buffer));
        printf("Input string: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}