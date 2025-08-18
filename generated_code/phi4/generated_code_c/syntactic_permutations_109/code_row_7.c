#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    
    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    executeCommand(argv[1]);

    return EXIT_SUCCESS;
}