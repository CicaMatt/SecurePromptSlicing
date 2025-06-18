#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1024
int getUserInfo(char *username){
    char command[SIZE];
    snprintf(command, SIZE, "id %s", username);
    FILE *fp = popen(command,"r");
    if(!fp){
        return -1;
    }
    
    char output[SIZE];
    int count=0;
    while(fgets(output, SIZE, fp)!=NULL){
        printf("%s",output);
        count++;
    }
    pclose(fp);
    return count;
}
int main(int argc, char *argv[]){
    if(argc<2){
        printf("Please provide a username\n");
        exit(1);
    }
    int ret=getUserInfo(argv[1]);
    if(ret==-1){
        perror("popen failed");
    }else{
        printf("%d lines printed\n",ret);
    }
    return 0;
}