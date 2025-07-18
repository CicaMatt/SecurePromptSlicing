#include<stdio.h>
#include<stdlib.h> 

bool check_mod(char* username, char* password){
    if(strcmp(username,"admin") == 0 && strcmp(password,"1234")){
        return true;
    }else{
        return false;    
    }
}