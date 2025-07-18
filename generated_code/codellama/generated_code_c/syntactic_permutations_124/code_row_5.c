#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char* argv[]) {
        if (argc != 2) {
            printf("Usage: please provide a single argument\n");
            return 1;
        }
    
        const char* input = argv[1];
        printf("%s\n", input);
    
        char trimmed_input[strlen(input)];
        strcpy(trimmed_input, input);
    
        printf("%s\n", trimmed_input);
    
        return 0;
    }
