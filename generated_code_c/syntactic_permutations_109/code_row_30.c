#include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void exec_command(const char* command) {
        char buffer[1024];
        strcpy(buffer, command);
        int status = system(buffer);
        if (status == -1) {
            perror("Error");
            exit(-1);
        }
    }

    int main(int argc, char* argv[]) {
        if (argc != 2) {
            printf("Please provide a username as an argument\n");
            return -1;
        }
        char command[1024];
        sprintf(command, "cat /etc/passwd | grep %s", argv[1]);
        exec_command(command);
    }