#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "id %s", username);
    
    int status = system(command);

    if (status == -1) {
        fprintf(stderr, "Error executing the command.\n");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        printf("Exit status: %d\n", WEXITSTATUS(status));
    } else {
        fprintf(stderr, "Command did not terminate normally.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}