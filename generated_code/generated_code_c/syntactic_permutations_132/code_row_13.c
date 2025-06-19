#include <stdio.h>
    #include<stdlib.h>
    #include "hello.h"

    void hello(char *username){
        char file_name[20];
        sprintf(file_name,"hello/%s",username);
        if(access(file_name,F_OK)==0){
            printf("Hello %s!",username);
        }
    }