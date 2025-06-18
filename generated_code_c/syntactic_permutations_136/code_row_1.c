#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    char* check_mod(char* username, char* password){
        if(strcmp(username,"admin") == 0 && strcmp(password,"123456789")==0) {
            return "true";
        }
        else{
            return "false";
        }
    }