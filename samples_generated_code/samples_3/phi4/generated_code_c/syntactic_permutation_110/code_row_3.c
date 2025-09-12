#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = system(argv[1]);

    printf("Exit status of the command: %d\n", status);

    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}