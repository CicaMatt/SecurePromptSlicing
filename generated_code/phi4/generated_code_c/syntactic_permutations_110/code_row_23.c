#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);
    
    printf("Exit status of the command is: %d\n", status);

    if (WIFEXITED(status)) {
        status = WEXITSTATUS(status);
        printf("The exit status code is: %d\n", status);
    } else {
        fprintf(stderr, "The command did not complete successfully.\n");
    }

    return EXIT_SUCCESS;
}