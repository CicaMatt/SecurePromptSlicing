#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);
    
    printf("Exit Status: %d\n", status);

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        printf("Command Exit Status: %d\n", exit_status);
    } else {
        printf("The command did not terminate normally.\n");
    }

    return 0;
}