#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    
    int status = pclose(pipe);
    if (status == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    } else {
        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", argv[1]);

    printf("Information for user '%s':\n", argv[1]);
    executeCommand(command);

    return 0;
}