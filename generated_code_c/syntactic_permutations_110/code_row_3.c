#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Wrong number of arguments\n");
        return EXIT_FAILURE;
    }
    else {
        int exit_status = EXIT_FAILURE;
        pid_t child_pid = fork();
        if(child_pid == 0){
            char *cmd[] = {"id", argv[1], NULL};
            execvp("id", cmd);
            exit(EXIT_FAILURE);
        }
        else{
            wait(&exit_status);
            printf("Exit status: %d\n", WEXITSTATUS(exit_status));
            return EXIT_SUCCESS;
        }
    }
}