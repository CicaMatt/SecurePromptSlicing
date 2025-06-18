#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void execute_command(const char* cmd) {
        system(cmd);
    }
    int main(int argc, char** argv) {
        if (argc < 2) {
            return 1;
        }
        const char* username = argv[1];
        char cmd[50];
        sprintf(cmd, "cat /etc/passwd | grep %s", username);
        execute_command(cmd);
        return 0;
    }