#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Error: No username provided");
        return 1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        execl("/usr/bin/id", "id", argv[1], NULL);
        exit(1);
    } else if (pid < 0) {
        printf("Error: Unable to fork process");
        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Exit status of command: %d", WEXITSTATUS(status));
        } else {
            printf("Error: Exit status not returned");
            return 1;
        }
    }
    return 0;
}