#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_id_command(const char *username) {
    pid_t pid;
    int status;
    char cmd[1024];

    snprintf(cmd, sizeof(cmd), "id %s", username);
    pid = fork();

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        _exit(127);
    } else if (pid < 0) {
        return -1;
    } else {
        waitpid(pid, &status, 0);
    }

    return WEXITSTATUS(status);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_id_command(argv[1]);
    printf("Exit status: %d\n", exit_status);
    return 0;
}