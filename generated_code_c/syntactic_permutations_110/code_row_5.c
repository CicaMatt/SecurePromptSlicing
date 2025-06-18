#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int runCommand(char *command);

int main (int argc, char* argv[]) {
  
    if(argc !=2){
        printf("Error: Invalid arguments\n");
        exit(1);
    }

    int status;
    status = runCommand(argv[1]);
    printf("Exit Status: %d\n",status);
    return 0;
}

int runCommand(char *command){

    char* arguments[]= {NULL};
    
    int retVal;
    if((retVal = execvp(command,arguments))<0) {
        printf("Error: Command could not be executed\n");
        exit(1);
    }

    return 0;
}