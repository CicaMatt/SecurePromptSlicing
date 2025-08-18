#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_id_command(const char *username) {
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        execlp("id", "id", username, NULL);
        _exit(127); // Return a non-zero status on exec failure
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return -1; // Return an error code if the child process did not exit normally
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_id_command(argv[1]);
    return exit_status;
}