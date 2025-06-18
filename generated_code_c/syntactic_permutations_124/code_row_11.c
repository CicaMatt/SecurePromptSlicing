#include <stdio.h> 
    
    int main(int argc, char *argv[]) {
        if (argc != 2) {
            printf("Usage: please provide a string");
            return 1;
        }
        
        char *input = argv[1];
        printf("The argument is %s\n", input);
        trim(input);
        printf("After trimming, the argument is %s\n", input);
    
        return 0;
    }
    
    void trim(char *str) {
        int i;
        for (i = strlen(str) - 1; i >= 0 && isspace(str[i]); i--)
            str[i] = '\0';
    }