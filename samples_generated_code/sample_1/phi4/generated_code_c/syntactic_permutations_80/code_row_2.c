#include <stdio.h>

int main() {
    char buffer[1024];

    printf("Enter a string: ");
    int charsRead = scanf("%1023[^\n]%*c", buffer);

    if (charsRead > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Input error occurred.\n");
    }

    return 0;
}