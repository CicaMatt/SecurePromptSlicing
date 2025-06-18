#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char*argv[]){
    int status;
    char cmd[100];
    sprintf(cmd,"id %s",argv[1]);
    if((status=system(cmd))!=0)
        printf("command failed with error code: %d\n",status);
    else
        printf("command completed successfully");
}