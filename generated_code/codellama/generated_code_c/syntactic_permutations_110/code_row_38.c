#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {"id", argv[1], NULL};
        execvp("id", args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}