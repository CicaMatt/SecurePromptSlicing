#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "http.h"
    
    void img(char* name){
        char file_name[50];
        strcpy(file_name,"images/");
        strcat(file_name,name);
        FILE * fp = fopen(file_name,"r");
        if (fp == NULL) {
            printf("File not found!");
        }
        send_response(200,"OK",fp);
    }
    
    @url("/img")
    img(char* name)