#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char **argv){
    // Check if the number of command line arguments is valid.
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        return 1;
    }
    char *username = argv[1];
    int exit_status;
    // Run the id command with the username as an argument.
    pid_t pid = fork();
    if (pid == 0) {
        execl("/usr/bin/id", "id", username, NULL);
    } else {
        wait(&exit_status);
        printf("Exit status: %d\n", exit_status);
    }
    return 0;
}