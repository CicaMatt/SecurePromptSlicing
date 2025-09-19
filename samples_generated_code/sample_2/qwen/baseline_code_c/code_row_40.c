#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* cmd) {
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return;

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            printf("%s", buffer);
    }
    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* username = argv[1];
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);

    executeCommand(command);

    return EXIT_SUCCESS;
}