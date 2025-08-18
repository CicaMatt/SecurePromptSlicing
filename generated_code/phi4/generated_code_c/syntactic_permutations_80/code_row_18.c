#include <stdio.h>

int main() {
    char buffer[1024];
    int chars_read = scanf("%1023[^\n]%*c", buffer);

    if (chars_read == 1) {
        printf("Input was successfully read. Here is the input string: %s\n", buffer);
    } else {
        printf("An error occurred during input.\n");
    }

    return 0;
}