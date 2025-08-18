#include <stdio.h>

int scan(char *buffer, size_t size) {
    if (size == 0) return 0;

    int result = scanf("%1023[^\n]%*c", buffer);
    return result > 0 ? result - 1 : 0;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    if (scan(buffer, sizeof(buffer)) == 0) {
        printf("No valid input or error occurred.\n");
    } else {
        printf("You entered: %s\n", buffer);
    }

    return 0;
}