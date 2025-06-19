#include <stdio.h>
    #include <string.h>
    
    int main(int argc, char *argv[]){
        if (argc != 2){
            printf("Usage: please provide a string\n");
            return 1;
        }
        char *input = argv[1];
        printf("Input: %s", input);
        char* trimmed_input = strtok(input, " ");
        printf("Trimmed Input: %s", trimmed_input);
        return 0;
    }