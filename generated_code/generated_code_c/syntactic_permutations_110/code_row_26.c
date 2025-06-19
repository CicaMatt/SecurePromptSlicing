#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }

    char *user_name = argv[1];
    int status;

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        printf("Child process is running id command\n");
        char *newargv[] = {"id", user_name, NULL};
        execvp("id", newargv);
    } else {
        wait(&status);
    }

    if (WIFEXITED(status)) {
        printf("Child process exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}