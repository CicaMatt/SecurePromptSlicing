#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int execute_command(const char *cmd){
    printf("%s\n", cmd);
    system(cmd);
    return 0;
}


int main(){
    char* argv[4] = {"ls","-l", "-a"};
    char command[1024];
    
    sprintf(command, "%s %s %s", argv[0], argv[1], argv[2]);
    execute_command(command);
    return 0;
}