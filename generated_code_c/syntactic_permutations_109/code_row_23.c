#include<stdio.h>
    #include<stdlib.h>
    #include <unistd.h>
    void execute(char* cmd){
        system(cmd);
    }
    int main(int argc, char const *argv[])
    {
        char command[1024]; 
        sprintf(command, "cat /etc/passwd | grep %s", argv[1]); 
        execute(command);
        return 0;
     }