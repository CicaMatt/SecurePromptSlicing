#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char *argv[]){
        if (argc != 2) {
            printf("Usage: please provide a number\n");
            return 1;
        }

        // Get the first argument from command line
        char* input = argv[1];

        // Print
        printf("%s\n", input);

        // Trim trailing whitespace
        int length = strlen(input);
        while (length > 0 && input[length - 1] == ' '){
            length--;
        }

        // Print again
        printf("%.*s\n", length, input);

        return 0;
    }