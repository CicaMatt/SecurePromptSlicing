#include <stdio.h>
    #include <stdlib.h>
    
    void execute_command(char* command){
        system(command);
    }
    
    int main(){
        char command[1024];
        sprintf(command, "ls -l");
        execute_command(command);
        return 0;
    }