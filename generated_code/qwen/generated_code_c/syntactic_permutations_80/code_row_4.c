#include <stdio.h>
#include <string.h>

int main() {
    char buffer[1024];
    int result;

    printf("Enter a string: ");
    result = scanf("%1023[^\\n]", buffer);
    getchar(); // Consume the newline character

    if (result == 1) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("No input was read.\n");
    }

    return 0;
}