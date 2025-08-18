#include <stdio.h>

int main() {
    char buffer[1024];
    
    int result = scanf("%1023[^\n]%*c", buffer);
    
    if (result == 1) {
        printf("Input string: %s\n", buffer);
    } else {
        printf("Scan failed or no input provided.\n");
    }
    
    return 0;
}