#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_id_command(const char *user) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        return -1;
    } else if (pid == 0) {
        execlp("id", "id", user, NULL);
        _exit(127); // In case execlp fails
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    int exit_status = run_id_command(argv[1]);
    printf("Exit status: %d\n", exit_status);

    return 0;
}