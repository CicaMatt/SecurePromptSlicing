#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>
    
    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Usage: %s username\n", argv[0]);
            return 1;
        }
        pid_t child = fork();
        if (!child) {
            execlp("/usr/bin/id", "id", argv[1], NULL);
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(child, &status, 0);
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }
        return 0;
    }