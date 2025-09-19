#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Exit Status: %d\n", WEXITSTATUS(status));
        } else {
            fprintf(stderr, "Child process did not terminate normally.\n");
            return EXIT_FAILURE;
        }
    } else {
        execlp("id", "id", argv[1], (char *)NULL);
        
        perror("execlp");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}