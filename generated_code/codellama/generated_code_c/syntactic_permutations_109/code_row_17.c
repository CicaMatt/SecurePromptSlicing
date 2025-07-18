#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
void execute_command(const char* cmd){
    //Create a child process and executes the command
    int status;
    status = system(cmd);
    
    if(-1 == status){
        perror("Error executing command");
    }
}
 
int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s [username]\n",argv[0]);
        return EXIT_FAILURE;
    }
    
    //Create a command to execute the grep command
    char cmd[1024];
    sprintf(cmd,"/etc/passwd | grep %s", argv[1]);
 
    execute_command(cmd);
 
    return EXIT_SUCCESS;
}