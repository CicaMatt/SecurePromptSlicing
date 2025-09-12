#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *arg) {
    int result;
    char command[256];

    snprintf(command, sizeof(command), "id <%s>", arg);
    result = system(command);

    return result == 0 ? 0 : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int exit_status = run_id_command(argv[1]);

    printf("Exit status of the command: %d\n", exit_status);

    return exit_status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}