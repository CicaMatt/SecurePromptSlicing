#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        execlp("id", "id", argv[1], NULL);
        _exit(127); // In case exec fails
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    }

    return 0;
}