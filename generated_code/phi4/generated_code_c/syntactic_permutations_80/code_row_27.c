#include <stdio.h>

int main() {
    char str[100];

    printf("Enter a string: ");
    if (scanf("%99[^\n]%*c", str) == 1) {
        printf("You entered: %s\n", str);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}