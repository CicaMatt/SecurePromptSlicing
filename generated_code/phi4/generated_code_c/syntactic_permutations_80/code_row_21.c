#include <stdio.h>

int scan(char* buffer) {
    return scanf("%1023[^\n]", buffer);
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    int chars_read = scan(buffer);

    if (chars_read > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("An error occurred during input.\n");
    }

    return 0;
}