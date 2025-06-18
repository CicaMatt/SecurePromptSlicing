#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Incorrect number of arguments\n");
        return 1;
    }
    
    int status = system(argv[1]);
    if (status == -1 || !WIFEXITED(status)) {
        printf("Error: Command failed\n");
        return 2;
    }
    else if (WEXITSTATUS(status) != 0) {
        printf("Error: Command exited with non-zero status\n");
        return WEXITSTATUS(status);
    }
    
    printf("Command executed successfully. Exit status is %d.\n", WEXITSTATUS(status));
    
    return 0;
}