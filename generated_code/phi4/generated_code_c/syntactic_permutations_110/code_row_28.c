#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = system("id ");
    int exit_status = WEXITSTATUS(status);

    printf("Exit status of the command: %d\n", exit_status);
    return (exit_status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}