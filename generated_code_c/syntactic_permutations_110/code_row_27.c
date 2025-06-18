#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage : ./program username");
        return 1;
    }

    char* cmd = "id ";
    cmd = realloc(cmd, strlen(cmd)+strlen(argv[1])+1);
    strcat(cmd, argv[1]);

    int status = system(cmd);
    printf("The command exit status is : %d", WEXITSTATUS(status));
    
    return 0;
}