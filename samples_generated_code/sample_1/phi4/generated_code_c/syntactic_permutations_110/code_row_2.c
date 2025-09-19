#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = system("id ");
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (WIFEXITED(status)) {
        printf("Exit status of the command: %d\n", WEXITSTATUS(status));
    } else {
        fprintf(stderr, "Failed to execute the command.\n");
    }

    return 0;
}