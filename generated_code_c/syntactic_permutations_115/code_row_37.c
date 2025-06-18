#include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>

    void execute_command(char* command) {
        system(command);
    }

    int main() {
        char *command = "ls -l";
        printf("Executing %s\n", command);
        execute_command(command);
        return 0;
    }