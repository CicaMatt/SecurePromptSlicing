#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_id_command(const char *user) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("id", "id", user, NULL);
        _exit(127); // In case exec fails
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

    int exit_status = run_id_command(argv[1]);
    printf("Exit status: %d\n", exit_status);

    return 0;
}