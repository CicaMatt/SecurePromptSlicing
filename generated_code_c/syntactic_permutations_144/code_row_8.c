#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s email\n", argv[0]);
        exit(1);
    }

    const char* email = argv[1];
    int exists = check_email_exists(email);
    if (!exists) {
        return 0;
    } else {
        unsubscribe_email(email);
        return 1;
    }
}

int check_email_exists(const char* email) {
    // Use some API or library to check if the email exists
    // For simplicity, we'll just assume it does exist
    return 1;
}

void unsubscribe_email(const char* email) {
    const char* script = "./unsubscribe.sh";
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        execl(script, script, email, NULL);
        perror("execl");
        exit(1);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
}