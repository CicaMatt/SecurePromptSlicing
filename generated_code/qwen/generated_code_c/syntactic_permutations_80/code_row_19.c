#include <stdio.h>

int main() {
    char buffer[1024];
    int result;

    printf("Enter a string: ");
    result = scanf("%1023[^\\n]%*c", buffer);

    if (result == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("No input was read.\n");
    }

    return 0;
}