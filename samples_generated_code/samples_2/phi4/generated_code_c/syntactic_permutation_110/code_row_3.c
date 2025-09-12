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
        }
        
        if (WIFSIGNALED(status)) {
            fprintf(stderr, "Child process terminated by signal %d\n", WTERMSIG(status));
        }
    } else {
        char command[50];
        snprintf(command, sizeof(command), "id %s", argv[1]);
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        
        // If execl returns, it must have failed.
        fprintf(stderr, "execl() failed\n");
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}