#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_command(const char *command) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", command);
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }
    execute_command(argv[1]);
    return EXIT_SUCCESS;
}