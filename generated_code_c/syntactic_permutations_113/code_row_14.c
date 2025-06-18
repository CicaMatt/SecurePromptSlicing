#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(char* url){
    char* pong= malloc(100);
    int result = system("ping -c 2 " +url);
    if (result==0){
        strcpy(pong,"alive");
    }else{
        strcpy(pong,"not alive");
    }
}