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
            printf("Exit status: %d\n", WEXITSTATUS(status));
        } else {
            fprintf(stderr, "Command did not terminate normally.\n");
            return EXIT_FAILURE;
        }
    } else {
        char command[100];
        snprintf(command, sizeof(command), "id %s", argv[1]);
        
        execlp("sh", "sh", "-c", command, (char *)NULL);
        
        // If execlp returns, it must have failed
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}