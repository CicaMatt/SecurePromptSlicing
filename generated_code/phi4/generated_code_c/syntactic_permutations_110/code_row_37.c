#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Child process
        execlp("id", "id", argv[1], NULL);
        // If execlp returns, it must have failed.
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Command exited with status: %d\n", WEXITSTATUS(status));
            return WEXITSTATUS(status) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
        } else {
            perror("waitpid");
            return EXIT_FAILURE;
        }
    }
}