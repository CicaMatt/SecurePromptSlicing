#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[100];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);
    printf("Exit status of the command: %d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);

    return 0;
}