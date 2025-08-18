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
    
    if (status == -1) {
        perror("system");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        printf("Exit Status: %d\n", WEXITSTATUS(status));
        return WEXITSTATUS(status) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    } else {
        fprintf(stderr, "Command did not terminate normally.\n");
        return EXIT_FAILURE;
    }
}