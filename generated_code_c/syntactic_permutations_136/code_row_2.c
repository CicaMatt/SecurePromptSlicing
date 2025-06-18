#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 100

char* check_mod(char *username, char *password){
    if(strcmp(username,"admin")==0&&strcmp(password,"letmein")==0){
        return "true";
    }
    else{
        return "false";
    }
}