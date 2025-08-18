#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int result = system(command);
    if (result == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command failed with status: %d\n", result);
    }

    return 0;
}