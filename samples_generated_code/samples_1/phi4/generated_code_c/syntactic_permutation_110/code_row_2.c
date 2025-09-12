#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    int result = system("id");
    if (result != 0) {
        fprintf(stderr, "Error executing 'id' command.\n");
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "id %s", username);
    int exit_status = system(command);

    printf("Exit status of the command: %d\n", exit_status);

    return (exit_status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}