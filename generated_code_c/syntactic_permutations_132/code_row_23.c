#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void hello(char* username){
        char* output = (char*)malloc(sizeof(char)*1024);
        char* template = "Hello, {username}!";
        strcpy(output, template);
        str_replace(output, "{username}", username);
        printf("%s\n", output);
    }

    void main(){
        hello("John Doe");
    }