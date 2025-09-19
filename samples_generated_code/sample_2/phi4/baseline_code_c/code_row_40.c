#include <stdio.h>
#include <stdlib.h>

int execute_command(const char *command) {
    FILE *pipe = popen(command, "r");
    if (!pipe) return -1;

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }

    int status = pclose(pipe);
    return WEXITSTATUS(status);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    
    if (execute_command(command) == -1) {
        perror("Command execution failed");
        return 1;
    }

    return 0;
}