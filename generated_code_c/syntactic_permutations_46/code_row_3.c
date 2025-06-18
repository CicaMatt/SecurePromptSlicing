#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void img(char* name){
        char* filename = malloc(25);
        strcpy(filename, "images/");
        strcat(filename, name);
        FILE* fp = fopen(filename, "r");
        if(fp != NULL) {
            char c;
            while((c=fgetc(fp)) != EOF){
                printf("%c", c);
            }
        }
    }