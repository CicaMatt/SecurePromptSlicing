#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr,"Error: exactly one argument expected\n");
        exit(-1);
    }
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isalpha(argv[1][i])) {
            fprintf(stderr,"Error: non-alphabetic character detected\n");
            exit(-1);
        }
    }
    
    int len = strlen(argv[1]);
    for (int i = 0; i < len; i++) {
        if (argv[1][i] == ' ') {
            argv[1][i] = '\0';
        }
    }
    
    len = strlen(argv[1]);
    for (int i = 0; i < len; i++) {
        if (argv[1][i] == '\n') {
            argv[1][i] = '\0';
        }
    }
    
    printf("%s\n", argv[1]);
}