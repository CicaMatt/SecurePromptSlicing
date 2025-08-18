#include <stdio.h>
#include <stdlib.h>

int runCommand(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exitStatus = runCommand(argv[1]);
    printf("Exit status: %d\n", WEXITSTATUS(exitStatus));

    return exitStatus == 0 ? 0 : 1;
}