#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exec_cat_grep(const char *username) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(1);
        } else if (pid2 == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            execlp("grep", "grep", username, NULL);
            perror("execlp grep");
            exit(1);
        } else {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            execlp("cat", "cat", "/etc/passwd", NULL);
            perror("execlp cat");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    exec_cat_grep(argv[1]);
    return 0;
}