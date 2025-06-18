#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 2) return 1;
    
    // Get the first argument and get rid of trailing whitespace
    char* arg = argv[1];
    int length = strlen(arg);
    while (length > 0 && arg[length - 1] == ' ') {
        length--;
    }
    
    // Print out the trimmed argument
    for (int i = 0; i < length; i++) {
        printf("%c", arg[i]);
    }
    printf("\n");
    
    return 0;
}