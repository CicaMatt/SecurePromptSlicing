#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_user_id(const char *username) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "id %s", username);
    pid_t pid = fork();
    if (pid == 0) {
        execlp("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        exit(127); // Fallback in case exec fails
    } else {
        int status;
        wait(&status);
        return WEXITSTATUS(status);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_user_id(argv[1]);
    printf("Exit status: %d\n", exit_status);
    return exit_status;
}