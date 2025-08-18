#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int get_user_info(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "id %s", username);
    int status;
    pid_t pid = fork();
    if (pid == 0) {
        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(127); // Fallback exit status in case of exec failure
    } else {
        wait(&status);
        return WEXITSTATUS(status);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = get_user_info(argv[1]);
    printf("Exit status: %d\n", exit_status);
    return exit_status;
}