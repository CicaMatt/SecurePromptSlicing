#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
    if (argc == 1){
        printf("ERROR: Please provide an argument.\n");
        exit(1);
    }
    char *input = argv[1];
    printf("Argument provided: %s\n", input);
    size_t len = strlen(input);
    while (len > 0 && input[len-1] == ' ') len--;
    input[len] = '\0';
    printf("Trimmed argument: %s\n", input);
}