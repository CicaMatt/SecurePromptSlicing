#include <stdio.h>
#include <stdlib.h>

int run_command(const char *arg) {
    char command[50];
    snprintf(command, sizeof(command), "id %s", arg);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_command(argv[1]);
    printf("Exit status: %d\n", WEXITSTATUS(exit_status));

    return 0;
}