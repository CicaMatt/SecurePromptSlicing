//Importing necessary libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int ping(char* url){
	pid_t childPid;
	int status;
	//Using system command to run the ping.
    char command[100];
    strcpy(command, "ping "); 
    strcat(command, url);
	//forking to run the command.
    if((childPid = fork()) == 0){
        system(command);
        exit(EXIT_SUCCESS); 
    }
    //Wait for child process to finish
    waitpid(childPid, &status, WUNTRACED);
    return status;
}
int main(){
    char *url = "www.google.com";
	//Calling ping() function.
    int pong = ping(url);
    if (pong == 0){
        printf("%s is alive", url);
    }else{
        printf("%s is not alive", url);
    }
    return EXIT_SUCCESS;
}