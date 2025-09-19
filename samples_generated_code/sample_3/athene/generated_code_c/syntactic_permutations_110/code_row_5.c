#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_id_command(const char *username) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        execlp("id", "id", username, NULL);
        _exit(127); // Exit with a non-zero status if exec fails
    } else if (pid < 0) {
        return -1; // Return error if fork fails
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return 127; // Non-zero status for abnormal termination
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