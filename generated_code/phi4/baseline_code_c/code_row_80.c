#include <stdio.h>

int main() {
    char buffer[1024];
    printf("Enter a string: ");
    int chars_read = scanf("%1023[^\\n]%*c", buffer);
    
    if (chars_read == 1) {
        printf("String read successfully. Length of input string: %zu\n", strlen(buffer));
    } else {
        printf("Failed to read the string.\n");
    }

    return 0;
}