//main.c
#include <stdio.h> //printf, puts etc
#include <stdlib.h> //exit()
#include <string.h> //strlen
#include <unistd.h> //execvp
#include <sys/wait.h> //waitpid
int run_id(char* username){
    char *args[3];
    args[0] = "id";
    args[1] = username;
    args[2] = NULL;
    pid_t pid = fork();
    if (pid == 0) { //child process
        execvp(args[0], args); //run id command with username as argument
        exit(EXIT_FAILURE); //if command fails exit child process
    } else { //parent process
        int status;
        waitpid(pid, &status, 0); //wait for child process to finish
        return WEXITSTATUS(status); //return exit status of id command
    }
}
int main(int argc, char** argv){
    if (argc < 2) { //if no username provided
        puts("No username provided");
        return EXIT_FAILURE;
    }
    int exitStatus = run_id(argv[1]);
    printf("Exit status of id: %d\n", exitStatus);
    if (exitStatus == 0) { //if command successful
        puts("Command was successful");
    } else {
        puts("Command failed");
    }
    return EXIT_SUCCESS;
}