#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int run_id_command(char *arg) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", arg);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = run_id_command(argv[1]);

    printf("Exit status of the command: %d\n", status);

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}