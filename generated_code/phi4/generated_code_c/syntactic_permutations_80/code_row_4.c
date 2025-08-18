#include <stdio.h>

int scan(char *buffer, int max_size) {
    return scanf("%1023[^\n]%*c", buffer);
}

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    
    if (scan(buffer, sizeof(buffer)) > 0) {
        printf("You entered: %s\n", buffer);
    } else {
        printf("Failed to read input.\n");
    }
    
    return 0;
}