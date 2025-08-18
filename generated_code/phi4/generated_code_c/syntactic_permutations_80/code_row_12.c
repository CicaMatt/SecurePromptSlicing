#include <stdio.h>

int scan(char *buffer, size_t size) {
    if (buffer == NULL || size <= 1) {
        return -1;
    }
    return scanf("%1023[^\n]%*c", buffer);
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int chars_read = scan(buffer, sizeof(buffer));
    
    if (chars_read > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input or no input provided.\n");
    }
    
    return 0;
}