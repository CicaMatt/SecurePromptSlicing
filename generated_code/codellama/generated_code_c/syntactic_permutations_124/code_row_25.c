#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 256
int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Invalid number of arguments");
        exit(1);
    }
    char input[MAX_BUF];
    strcpy(input, argv[1]);
    printf("%s", input);
    input[strlen(input) - 1] = '\0';
    printf("%s", input);
    return 0;
}