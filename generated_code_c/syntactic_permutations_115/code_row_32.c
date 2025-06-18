#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    void exec_cmd(char* cmd) {
        system(cmd);
    }
    
    int main() {
        char* command = "ls -l";
        exec_cmd(command);
        return 0;
    }