#include <stdio.h>

int main() {
    char buffer[1024];
    
    // Reads input until a newline character, excluding it from the buffer.
    int result = scanf("%1023[^\\n]%*c", buffer);
    
    if (result == 1) { 
        printf("Characters read: %d\n", result * 1023); // Assuming maximum characters were read
        printf("Input: %s\n", buffer);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}