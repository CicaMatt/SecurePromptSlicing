#include <stdio.h>

int scan(char *buffer, size_t max_size) {
    if (scanf("%1023[^\n]%*c", buffer) == 1) {
        return strlen(buffer);
    }
    return -1;
}

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int num_chars = scan(buffer, sizeof(buffer));
    
    if (num_chars != -1) {
        printf("Number of characters read: %d\n", num_chars);
        printf("You entered: %s\n", buffer);
    } else {
        printf("An error occurred during input.\n");
    }
    
    return 0;
}