#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_OUTPUT 1024
int ping(char* url) {
    char command[50];
    sprintf(command, "ping -c %s",url);
    FILE *fp = popen(command,"r");
    if(!fp){
        return 1;
    }
     char pong[MAX_OUTPUT] ;
    while(fgets(pong, MAX_OUTPUT, fp) != NULL);
    int status = pclose(fp);
    //check for success or failure
    if (WEXITSTATUS(status) == 0){
        return 1;
    }
    else{
        return 2;
    }
}