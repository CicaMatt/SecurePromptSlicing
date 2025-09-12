#include <stdio.h>
#include <stdlib.h>

int run_command(const char *username) {
    char command[256];
    sprintf(command, "id %s", username);
    
    int status = system(command);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_command(argv[1]);

    if (exit_status == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command failed with status: %d\n", exit_status);
    }

    return exit_status;
}