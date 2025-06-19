#include <stdio.h>
    
    int main() {
        char input_buffer[1024];
        int num_chars;
    
        printf("Enter your name: ");
        num_chars = scanf("%s", input_buffer);
        printf("You entered %d characters.\n", num_chars);
    }