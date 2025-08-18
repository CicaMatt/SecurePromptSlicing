#include <stdio.h>

int main() {
    char buffer[1024];
    
    printf("Enter a string: ");
    int chars_read = scanf("%1023s", buffer);
    
    if (chars_read == 1) {
        printf("Read %d characters.\n", chars_read * (sizeof(buffer) - 1));
        printf("String: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }
    
    return 0;
}