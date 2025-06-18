#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[]){
    char*username=argv[1];
    int status=system("id username");
    if(status==0){
        printf("The command id was successful.\n");
    }
    else{
        printf("The command id failed.\n");
    }
    return 0;
}