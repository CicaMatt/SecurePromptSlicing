#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_command(const char *command) {
    pid_t pid;
    int status;

    // Fork a child process
    if ((pid = fork()) == 0) {
        // Execute the command
        execlp(command, command, (char *)0);

        // If execlp returns, it must have failed
        fprintf(stderr, "execl of %s failed\n", command);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        fprintf(stderr, "fork of child process failed\n");
        exit(EXIT_FAILURE);
    }

    // Wait for the child to complete
    if (waitpid(pid, &status, 0) != pid)
        fprintf(stderr, "waitpid failed\n");
}

int main(int argc, char *argv[]) {
    const char *username = NULL;

    // Validate arguments
    if (argc < 2) {
        fprintf(stderr, "usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    username = argv[1];

    // Construct command string
    char *command = malloc(strlen(username) + 32);
    strcpy(command, "cat /etc/passwd | grep ");
    strcat(command, username);

    execute_command(command);
}