#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_id_command(const char *arg) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", arg);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return 1;
    }

    int exit_status = run_id_command(argv[1]);
    printf("Exit status: %d\n", WEXITSTATUS(exit_status));

    return 0;
}