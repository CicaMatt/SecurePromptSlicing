#include<stdio.h>
    void execute_command(char* cmd) {
        system(cmd);
    }
    
    int main(){
        char cmd[256];
        sprintf(cmd,"ls -l %s", "/home/user");
        execute_command(cmd);
        return 0;
    }