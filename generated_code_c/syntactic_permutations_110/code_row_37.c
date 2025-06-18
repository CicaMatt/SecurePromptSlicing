#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char**argv){
    if(argc<2){
        return 1;
    }
    char cmd[50];
    sprintf(cmd,"id %s",argv[1]);
    int status=system(cmd);
    printf("%d\n",status);
}