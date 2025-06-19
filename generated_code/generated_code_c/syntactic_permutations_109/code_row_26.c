#include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <unistd.h>

    int main(int argc, char *argv[]) {
        pid_t pid;
        if (argc != 2) {
            printf("Usage: %s username\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == 0) { // Child process
            char *cmd[] = {"/bin/grep", "-r", "username", "/etc/passwd", NULL};
            execvp(cmd[0], cmd);
            printf("Child: %d\n", getpid());
        } else if (pid > 0) { // Parent process
            wait(NULL);
            printf("Parent: %d\n", getpid());
        }
    
    return 0;
    }