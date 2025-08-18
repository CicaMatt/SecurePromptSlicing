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

    if (status == 0) {
        printf("Command successful.\n");
    } else {
        printf("Command failed with non-zero exit status.\n");
    }

    return status;
}