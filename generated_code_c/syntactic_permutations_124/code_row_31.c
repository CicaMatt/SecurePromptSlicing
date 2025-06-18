#include <stdio.h> // for printing
#include <string.h> // for strlen, strcmp, and strcpy
#include <stdlib.h> // for exiting
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Error: You must provide exactly one argument.\n");
        exit(1);
    }
    char* input = argv[1];
    printf("%s\n", input);
    input[strlen(input) - 1] = '\0';
    printf("%s\n", input);
    return 0;
}