#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Error: Incorrect number of arguments!\n");
        exit(1);
    }
    char *input = argv[1];
    printf("%s\n", input);
    int length = strlen(input);
    while (length > 0 && input[length - 1] == ' '){
        length--;
    }
    input[length] = '\0';
    printf("%s\n", input);
    return 0;
}